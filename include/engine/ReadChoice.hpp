#pragma once
#include <string>
#include <iostream>

inline int readChoice(int min, int max) {
    while (true) {
        std::cout << "Ваш выбор: ";
        std::string line;
        std::getline(std::cin, line);
        try {
            int value = std::stoi(line);
            if (value >= min && value <= max)
                return value;
        } catch (...) {}
        std::cout << "Ожидается число от " << min << " до " << max << "\n";
    }
}