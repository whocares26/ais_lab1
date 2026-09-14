#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Rule.hpp"
#include "Object.hpp"
#include "KnowledgeBase.hpp"
#include <set>
namespace db {
    enum class FactAddResult {
        Added, AlreadyExists, Conflict
    };
    
    class WorkingMemory {
    public:
        FactAddResult addFact(const Fact& fact);
        bool hasFact(const std::string &obj, const std::string& val) const;
        const std::unordered_map<std::string, std::set<std::string>>& getMemory() const;
        WorkingMemory(const KnowledgeBase& kb) : m_kb(kb) {
            clear();
        }
        void clear() {
            m_memory.clear();
            for (const auto& f : m_kb.getInitFacts()) {
                m_memory[f.first].insert(f.second);
            }
        }
        bool isKnown(const std::string& obj) const;
    private:
        std::unordered_map<std::string, std::set<std::string>> m_memory;
        const KnowledgeBase& m_kb;
    };
}
