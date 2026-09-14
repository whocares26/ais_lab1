#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "db/Rule.hpp"
#include "db/Object.hpp"
#include "db/KnowledgeBase.hpp"
#include "db/WorkingMemory.hpp"
namespace en {
    class ForwardChainer {
    public:
        bool run();
    private:
        std::unordered_map<std::string, std::string> results;
    };
}
