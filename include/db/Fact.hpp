#pragma once
#include <string>
namespace db {
    struct Fact {
        std::string m_object;
        std::string m_value;
    };

    inline void from_json(const nlohmann::json& j, Fact& fact) {
        j.at("object").get_to(fact.m_object);
        j.at("value").get_to(fact.m_value);
    }
}
