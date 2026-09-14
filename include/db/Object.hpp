#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace db {
    struct Object {
        std::string m_prompt;
        std::vector<std::string> m_values;
        bool m_multi;
    };

    inline void from_json(const nlohmann::json& j, Object& obj) {
        obj.m_prompt = j.value("prompt", "");
        j.at("values").get_to(obj.m_values);
        j.at("multi").get_to(obj.m_multi);
    }

    inline void to_json(nlohmann::json& j, const Object& obj) {
        j = nlohmann::json {
            {"prompt", obj.m_prompt},
            {"values", obj.m_values},
            {"multi", obj.m_multi}
        };
    }
}
