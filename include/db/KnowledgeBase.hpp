#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Rule.hpp"
namespace db {
    inline const std::string db_path = "../data/rules.json";
    class KnowledgeBase {
    public:
        bool load();
        const std::vector<Rule>& getRules() const;
        const std::unordered_map<std::string, Object>& getObjects() const;
        bool removeRule(int id);
        bool replaceRule(int id, const Rule& rule); // изменение
        bool addRule(const Rule& rule);
        const Rule* findRule(int id) const;
        bool save() const;
        const std::unordered_map<std::string, std::string>& getInitFacts() const;
    private:
        std::vector<Rule> m_rules;
        std::unordered_map<std::string, Object> m_objects;
        std::unordered_map<std::string, std::string> m_initial_facts;
    };
}
