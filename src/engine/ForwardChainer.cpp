#include <string>
#include <vector>
#include <unordered_map>
#include "db/Rule.hpp"
#include "db/Object.hpp"
#include "db/KnowledgeBase.hpp"
#include "db/WorkingMemory.hpp"
#include "engine/ForwardChainer.hpp"
#include "engine/ReadChoice.hpp"
#include <iostream>

namespace engine {

        std::string ForwardChainer::selectQuestion(const std::vector<db::Rule>& rules) const {
            int min = 100;
            std::string result = "";
            for (const auto& rule : rules) {
                bool dead = false;
                std::vector<std::string> unknowns;
                for (const auto& condition : rule.m_condition) {
                    if (m_wm.isKnown(condition.m_object)) {
                        if (!m_wm.hasFact(condition.m_object, condition.m_value)) {
                            dead = true;       // известно другое значение
                            break;
                        }
                        // иначе противоречий нет
                    } else {
                        if (m_unknown.count(condition.m_object) > 0) {
                            dead = true;          // ответа уже не будет, правило не сработает
                            break;
                        }
                        if (m_unknown.count(condition.m_object) == 0 && m_kb.getObjects().at(condition.m_object).m_prompt != "")
                            unknowns.push_back(condition.m_object);
                    }
                }
                if (dead || unknowns.empty())
                    continue;
                if (unknowns.size() < min) {
                    min = unknowns.size();
                    result = unknowns[0];
                }
            }
            return result;
        }

        bool ForwardChainer::askUser(const std::string& objName) {
            const auto& obj = m_kb.getObjects().at(objName);

            std::cout << obj.m_prompt << "\n";
            for (size_t i = 0; i < obj.m_values.size(); i++)
                std::cout << i + 1 << ". " << obj.m_values[i] << "\n";
            std::cout << obj.m_values.size() + 1 << ". Не знаю\n";

            int choice = readChoice(1, obj.m_values.size() + 1);

            if (choice == obj.m_values.size() + 1)
                return false;         // не знаю

            m_wm.addFact({objName, obj.m_values[choice - 1]});
            return true;
        }

        void ForwardChainer::run() {
            m_unknown.clear();
            const auto& ruleList = m_kb.getRules();
            while(true) {
                while(true) {
                    bool changed = false;
                    for (const auto& rule : ruleList) {
                        bool result = true;
                        for (int i = 0; i < rule.m_condition.size(); i++) {
                            if (!m_wm.hasFact(rule.m_condition[i].m_object, rule.m_condition[i].m_value)) {
                                result = false;
                                break;
                            }
                        }
                        if (result) {
                            switch (m_wm.addFact(rule.m_result)) {
                                case db::FactAddResult::Added:
                                    std::cout << "Правило " << rule.m_id << ": " << toString(rule)
                                    << "\n  → добавлено: " << toString(rule.m_result) << "\n";
                                    changed = true;
                                    break;
                                case db::FactAddResult::Conflict:
                                    std::cout << "Противоречие: правило " << rule.m_id
                                            << " выводит " << toString(rule.m_result)
                                            << ", но объект уже имеет другое значение\n";
                                    return;
                                case db::FactAddResult::AlreadyExists:
                                    
                                    break;
                            }
                        }
                    }
                    if (!changed) break;
                }
                const std::string& candidate = selectQuestion(ruleList);
                if (candidate.empty()) {
                    std::cout << "Новых сведений нет, вывод завершён\n";
                    return;
                }
                if (!askUser(candidate)) {
                    m_unknown.insert(candidate);   // не знаю — ищем следующего
                }
                // в любом случае возвращаемся к правилам             
            }
        }
    }
