#include "db/KnowledgeBase.hpp"
#include "db/Rule.hpp"
#include "db/Object.hpp"
#include <nlohmann/json.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <exception>
namespace db {
    bool KnowledgeBase::load() {
        using json = nlohmann::json;
        std::ifstream file(db_path);
        if (!file.is_open()) {
            return false;
        }
        try {
            json data = json::parse(file);
            file.close();
            std::string domain = data["domain"];
            m_goal_objects = data["goal_objects"].get<std::vector<std::string>>();
            m_objects = data["objects"].get<std::unordered_map<std::string, Object>>();
            m_initial_facts = data["initial_facts"].get<std::unordered_map<std::string, std::string>>();
            m_rules = data["rules"].get<std::vector<Rule>>();
        } catch(const std::exception& e) {
            std::cout<<e.what()<<std::endl;
            return false;
        }
        return true;
    }
    const std::vector<Rule>& KnowledgeBase::getRules() const {
        return m_rules;
    }
    const std::unordered_map<std::string, Object>& KnowledgeBase::getObjects() const {
        return m_objects;
    }
    bool KnowledgeBase::addRule(const Rule& rule) {
        auto temp = rule;
        int max_id = 0;
        for (const auto& x : m_rules) {
            if (x.m_id > max_id) max_id = x.m_id;
        }
        temp.m_id = max_id + 1;
        m_rules.push_back(temp);
        return save();
    }
    bool KnowledgeBase::addObject(const std::string& name, const Object& obj) {
        if (m_objects.find(name) != m_objects.end()) {
            return false;
        }
        m_objects[name] = obj;
        return save();
    }
    bool KnowledgeBase::addValue(const std::string& objName, const std::string& value) {
        auto it = m_objects.find(objName);
        if (it == m_objects.end())
            return false;

        auto& values = it->second.m_values;
        if (std::find(values.begin(), values.end(), value) != values.end())
            return false;

        values.push_back(value);
        return save();
    }
}
