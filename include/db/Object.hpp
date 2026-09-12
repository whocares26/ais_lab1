#pragma once
#include <string>
#include <vector>
namespace db {
    struct Object {
        std::string m_prompt;
        std::vector<std::string> values;
        bool multi;
    };
}
