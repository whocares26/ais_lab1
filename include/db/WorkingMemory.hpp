#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Rule.hpp"
#include "Object.hpp"
#include "KnowledgeBase.hpp"
namespace db {
    class WorkingMemory {
    public:
        bool addFact(const Fact& fact);
        bool hasFact(const Object& obj, const std::string& val);
        const std::vector<Fact>& getMemory() const;
    private:
        std::vector<Fact> m_memory;
    };
}
