#include "db/WorkingMemory.hpp"
#include "db/Fact.hpp"

namespace db {
    FactAddResult WorkingMemory::addFact(const Fact& fact) {
        if (m_memory.find(fact.m_object) != m_memory.end() &&
            m_memory[fact.m_object].find(fact.m_value) != m_memory[fact.m_object].end()) {
            return FactAddResult::AlreadyExists;
        }
        const auto& objects = m_kb.getObjects();
        if (m_memory.find(fact.m_object) != m_memory.end() &&
            !objects.at(fact.m_object).m_multi) {
            return FactAddResult::Conflict;
        }
        m_memory[fact.m_object].insert(fact.m_value);
        return FactAddResult::Added;
    }
    bool WorkingMemory::hasFact(const std::string &obj, const std::string& val) const {
        if (m_memory.find(obj) != m_memory.end() &&
            m_memory.at(obj).find(val) != m_memory.at(obj).end()) {
            return true;
        }
        return false;
    }
    bool WorkingMemory::isKnown(const std::string& obj) const {
            return m_memory.find(obj) != m_memory.end();
    }
    const std::unordered_map<std::string, std::set<std::string>>& WorkingMemory::getMemory() const {
        return m_memory;
    }
}