#pragma once
#include <string>
#include <nlohmann/json.hpp>
namespace db {
    struct Fact {
        std::string m_object;
        std::string m_value;
    };

    inline std::string toString(const Fact& fact) {
        return fact.m_object + "=" + fact.m_value;
    }

    inline void from_json(const nlohmann::json& j, Fact& fact) {
        j.at("object").get_to(fact.m_object);
        j.at("value").get_to(fact.m_value);
    }
    
    inline void to_json(nlohmann::json& j, const Fact& fact) {
        j = nlohmann::json {
            {"object", fact.m_object},
            {"value", fact.m_value}
        };
    }
}
