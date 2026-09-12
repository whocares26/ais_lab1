#pragma once
#include <string>
#include "Object.hpp"
#include <vector>
#include "Fact.hpp"
namespace db {
    struct Rule {
        std::vector<Fact> m_condition;
        Fact m_result;
        int m_id;
    };
}
