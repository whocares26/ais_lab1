#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "db/Rule.hpp"
#include "db/Object.hpp"
namespace db {
    inline const std::string db_path = "../data/rules.json";
    class KnowledgeBase {
    public:
        bool load();
        const std::vector<Rule>& getRules() const;
        const std::unordered_map<std::string, Object>& getObjects() const;
        bool removeRule(int id);
        bool replaceRule(int id, const Rule& rule); // изменение (замена)
        bool addRule(const Rule& rule);
        const Rule* findRule(int id) const;
        bool save() const;
        const std::unordered_map<std::string, std::string>& getInitFacts() const;
        bool addValue(const std::string& objName, const std::string& value);
        bool addObject(const std::string& name, const Object& obj);
        const std::vector<std::string>& getGoalObjects() const;
    private:
        std::vector<Rule> m_rules;
        std::unordered_map<std::string, Object> m_objects;
        std::unordered_map<std::string, std::string> m_initial_facts;
        std::vector<std::string> m_goal_objects;
    };
}
