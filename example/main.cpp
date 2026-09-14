#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "db/KnowledgeBase.hpp"
#include "db/WorkingMemory.hpp"
#include "engine/ForwardChainer.hpp"
#include "engine/ReadChoice.hpp"

#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define RESET   "\033[0m"

// Выбор объекта и его значения. Возвращает собранный факт.
db::Fact readFact(db::KnowledgeBase& kb) {
    std::cout << "Выберите существующий объект или создайте свой:\n";

    std::vector<std::string> names;
    for (const auto& pair : kb.getObjects())
        names.push_back(pair.first);

    for (int i = 0; i < names.size(); i++)
        std::cout << i + 1 << ". " << names[i] << "\n";
    std::cout << names.size() + 1 << ". Создать свой\n";

    std::string objName;
    int input = readChoice(1, names.size() + 1);

    if (input == names.size() + 1) {
        std::cout << "Введите имя объекта: ";
        std::getline(std::cin, objName);
        while (objName.empty()) {
            std::cout << "Имя не может быть пустым. Введите имя объекта: ";
            std::getline(std::cin, objName);
        }

        db::Object newObj;

        std::cout << "Введите текст вопроса (prompt): ";
        std::getline(std::cin, newObj.m_prompt);

        std::cout << "Может ли объект иметь несколько значений одновременно?\n"
                  << "1. Да\n"
                  << "2. Нет\n";
        newObj.m_multi = (readChoice(1, 2) == 1);

        std::cout << "Введите допустимые значения (пустая строка — конец ввода):\n";
        while (true) {
            std::string value;
            std::getline(std::cin, value);
            if (value.empty())
                break;
            newObj.m_values.push_back(value);
        }

        if (!kb.addObject(objName, newObj)) {
            std::cout << "Объект с таким именем уже существует, используется существующий\n";
        }
    } else {
        objName = names[input - 1];
    }

    const auto& obj = kb.getObjects().at(objName);

    std::cout << "Выберите существующее значение или создайте своё:\n";
    for (int j = 0; j < obj.m_values.size(); j++)
        std::cout << j + 1 << ". " << obj.m_values[j] << "\n";
    std::cout << obj.m_values.size() + 1 << ". Ввести новое значение\n";

    int valueChoice = readChoice(1, obj.m_values.size() + 1);

    if (valueChoice == obj.m_values.size() + 1) {
        std::cout<<"Введите новое значение: ";
        std::string val;
        std::getline(std::cin, val);
        if (!kb.addValue(objName, val)) {
            std::cout<<"Ошибка добавления значения!\n";
        }
        return {objName, val};
    }

    return {objName, obj.m_values[valueChoice - 1]};
}

int main() {
    auto knowledgeBase = std::make_unique<db::KnowledgeBase>();
    if (!knowledgeBase->load()) {
        std::cerr << "Ошибка чтения базы знаний\n";
        return 1;
    }
    db::WorkingMemory workingMemory(*knowledgeBase);
    engine::ForwardChainer chainer(*knowledgeBase, workingMemory);

    while (true) {
        std::cout << GREEN <<"\n=== Экспертная система ===\n"
                  << "1. Показать правила\n"
                  << "2. Добавить правило\n"
                  << "3. Изменить правило\n"
                  << "4. Удалить правило\n"
                  << "5. Показать стартовую ситуацию\n"
                  << "6. Запустить вывод\n"
                  << "0. Выход\n";

        int choice = readChoice(0, 6);
        switch (choice) {
            case 1: {
                for (const auto& rule : knowledgeBase->getRules())
                    std::cout << rule.m_id << ". " << toString(rule) << "\n";
                break;
            }

            case 2: {
                db::Rule rule;

                std::cout << "ВВОД УСЛОВИЯ\n";
                while (true) {
                    rule.m_condition.push_back(readFact(*knowledgeBase));
                    std::cout << "Нужен ли ещё факт в условие?\n"
                                << "1. Да\n"
                                << "2. Нет\n";
                    if (readChoice(1, 2) == 2)
                        break;
                }
                std::cout << "ВВОД ЗАКЛЮЧЕНИЯ\n";
                rule.m_result = readFact(*knowledgeBase);
                if (!knowledgeBase->addRule(rule)) {
                    std::cerr<<"Ошибка при добавлении правила!";
                }
                break;
            }

            case 3: {
                // "3. Изменить правило\n"
                const auto& list = knowledgeBase->getRules();
                for (const auto& rule : list)
                    std::cout << rule.m_id << ". " << toString(rule) << "\n";
                int id = -1; 
                while (knowledgeBase->findRule(id) == nullptr) {
                    std::cout << "Введите ID правила: ";
                    std::string line;
                    std::getline(std::cin, line);
                    try { id = std::stoi(line); } catch (...) { id = -1; }
                    if (knowledgeBase->findRule(id) == nullptr)
                        std::cout << "Нет правила с таким ID\n";
                }

                db::Rule rule;
                std::cout << "ВВОД УСЛОВИЯ\n";
                while (true) {
                    rule.m_condition.push_back(readFact(*knowledgeBase));
                    std::cout << "Нужен ли ещё факт в условие?\n"
                                << "1. Да\n"
                                << "2. Нет\n";
                    if (readChoice(1, 2) == 2)
                        break;
                }
                std::cout << "ВВОД ЗАКЛЮЧЕНИЯ\n";
                rule.m_result = readFact(*knowledgeBase);
                if (!knowledgeBase->replaceRule(id, rule)) {
                    std::cerr<<"Ошибка при изменении правила!";
                }       
                break;
            }

            case 4: {
                for (const auto& rule : knowledgeBase->getRules())
                    std::cout << rule.m_id << ". " << toString(rule) << "\n";
                int id = -1; 
                while (knowledgeBase->findRule(id) == nullptr) {
                    std::cout << "Введите ID правила: ";
                    std::string line;
                    std::getline(std::cin, line);
                    try { id = std::stoi(line); } catch (...) { id = -1; }
                    if (knowledgeBase->findRule(id) == nullptr)
                        std::cout << "Нет правила с таким ID\n";
                }
                if (!knowledgeBase->removeRule(id)) {
                    std::cout <<"Ошибка при удалении правила по ID\n";
                }
                break;
            }

            case 5: {
                const auto& facts = knowledgeBase->getInitFacts();
                std::cout<<"СТАРТОВЫЕ ФАКТЫ\n";
                for (const auto& fact : facts) {
                    std::cout<<fact.first<<"="<<fact.second<<std::endl;
                }
                break;
            }

            case 6: {
                workingMemory.clear();
                chainer.run();
                std::cout << "\n=== Рабочая база данных ===\n";
                for (const auto& obj : workingMemory.getMemory())
                    for (const auto& val : obj.second)
                        std::cout << obj.first << " = " << val << "\n";
                std::cout << "\n=== Заключение ===\n";
                bool any = false;
                for (const auto& goal : knowledgeBase->getGoalObjects()) {
                    const auto& mem = workingMemory.getMemory();
                    auto it = mem.find(goal);
                    if (it == mem.end()) continue;          // цель не выведена
                    any = true;
                    for (const auto& val : it->second)
                        std::cout << goal << " = " << val << "\n";
                }
                if (!any) {
                    std::cout << "Заключение не получено: недостаточно данных\n";
                }
                break;               
            }

            case 0:
                return 0;
        }
    }
}
