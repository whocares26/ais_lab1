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
        ForwardChainer(const db::KnowledgeBase& kb, db::WorkingMemory& wm);
        void run();
    private:
        const db::KnowledgeBase& m_kb;
        db::WorkingMemory& m_wm;
        std::set<std::string> m_unknown;   // объекты, про которые пользователь сказал "не знаю"
    };
}
