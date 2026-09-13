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
    while (true) {
            std::cout << "\n=== Экспертная система ===\n"
                      << "1. Показать правила\n"
                      << "2. Добавить правило\n"
                      << "3. Изменить правило\n"
                      << "4. Удалить правило\n"
                      << "5. Показать стартовую ситуацию\n"
                      << "6. Запустить вывод\n"
                      << "0. Выход\n"
                      << "Выбор: ";

            int choice;
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ожидается число\n";
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
                case 1: // 1. Показать правила\n
                    for (const auto& rule : knowledgeBase->getRules())
                        std::cout<<rule.m_id<<". "<<toString(rule)<<std::endl;
                    break;
                case 2:
                    // 2. Добавить правило\n"
                    break;
                case 3:
                    // "3. Изменить правило\n"
                    break;
                case 4:
                    // 4. Удалить правило\n"
                    break;
                case 5:
                    // 5. Показать стартовую ситуацию\n"
                    break;
                case 6:
                    // 6. Запустить вывод\n"
                    // создать WorkingMemory из kb.getInitFacts(),
                    // запустить ForwardChainer, напечатать рабочую БД и Заключение
                    break;
                case 0:
                    return 0;
                default:
                    std::cout << "Нет такого пункта\n";
            }
        }

    return 0;
}
