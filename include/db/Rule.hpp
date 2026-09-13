#pragma once
#include <string>
#include "Object.hpp"
#include <vector>
#include "db/Fact.hpp"
namespace db {
    struct Rule {
        std::vector<Fact> m_condition;
        Fact m_result;
        int m_id;
    };

    inline void from_json(const nlohmann::json& j, Rule& rule) {
        j.at("id").get_to(rule.m_id);
        j.at("if").get_to(rule.m_condition);
        j.at("then").get_to(rule.m_result);
    }
}
