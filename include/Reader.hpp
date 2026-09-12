#pragma once
#include <string>
#include <vector>
#include "Rule.hpp"
namespace db {
    std::string db_path = "../data/rules.json";
    class Reader {
    public:
        void parseJson();
        void expandWorkingMemory(Object object);
        void expandRules(Rule rule);
        const std::vector<Rule> getRules();
        const std::vector<Rule> getWorkingMemory();
    private:
        std::vector<Rule> m_rules;
        std::vector<Object> m_working_memory;
    }
}
