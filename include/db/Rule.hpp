#pragma once
#include <string>
#include "Object.hpp"
#include <vector>
namespace db {
    struct Rule {
        std::vector<Object> m_condition;
        Object m_result;
        int m_id;
    };
}
