#pragma once
#include <string>
#include "object.hpp"
#include <vector>
namespace db {
    class Rule {
    public:
        Rule(int id, Object result, std::vector<Object> condition) :
            m_id(id), m_result(result), m_condition(condition) {}
        const std::vector<Object> getCondition();
        const int getId();
        const getResult();
    private:
        std::vector<Object> m_condition;
        Object m_result;
        int m_id;
    };
}
