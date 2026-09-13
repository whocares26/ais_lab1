#pragma once
#include <string>
#include <vector>
#include "db/Fact.hpp"
#include <nlohmann/json.hpp>
namespace db {
    struct Rule {
        std::vector<Fact> m_condition;
        Fact m_result;
        int m_id;
    };

    inline std::string toString(const Rule& rule) {
        std::string res = "ЕСЛИ ";
        for (int i = 0; i < rule.m_condition.size(); i++) {
            if (i > 0)
                res += " И ";
            res += toString(rule.m_condition[i]);
        }
        return res + " ТО " + toString(rule.m_result);
    }

    inline void from_json(const nlohmann::json& j, Rule& rule) {
        j.at("id").get_to(rule.m_id);
        j.at("if").get_to(rule.m_condition);
        j.at("then").get_to(rule.m_result);
    }
}
