#pragma once
#include <string>
#include "object.hpp"
#include <vector>
namespace db {
    class Rule {
        std::vector<Object> m_condition;
        db::Object m_result;
        int m_id;
    public:
        void setValue(std::string val);
        std::string getValue();
        std::string getPromt();
    };
}
