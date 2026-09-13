#include "db/KnowledgeBase.hpp"
#include "db/Rule.hpp"
#include "db/Object.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <exception>
namespace db {
    bool KnowledgeBase::load() {
        using json = nlohmann::json;
        std::ifstream file(db_path);
        if (!file.is_open()) {
            return 1;
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
            return 1;
        }
        return 0;
    }
}
