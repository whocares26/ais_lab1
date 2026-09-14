#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "db/Rule.hpp"
#include "db/Object.hpp"
#include "db/KnowledgeBase.hpp"
#include "db/WorkingMemory.hpp"

namespace engine {
    class ForwardChainer {
    public:
        ForwardChainer(const db::KnowledgeBase& kb, db::WorkingMemory& wm) : m_kb(kb), m_wm(wm) {}
        void run();
        std::string selectQuestion(const std::vector<db::Rule>& rules) const;
        bool askUser(const std::string& objName);
    private:
        const db::KnowledgeBase& m_kb;
        db::WorkingMemory& m_wm;
        std::set<std::string> m_unknown;   // объекты, про которые пользователь сказал "не знаю"
    };
}
