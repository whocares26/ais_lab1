#include <iostream>
#include <memory>
#include "db/KnowledgeBase.hpp"
int main() {
    // загрузка правил и стартовых фактов в память
    auto knowledgeBase = std::make_unique<db::KnowledgeBase>();
    if (knowledgeBase->load()) {
        std::cerr<<"Ошибка чтения базы знаний\n";
        return 1;
    }

    return 0;
}
