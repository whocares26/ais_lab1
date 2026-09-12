#pragma once
#include <string>
namespace db {
    class Object {
        std::string m_promt;
        std::string m_value;
    public:
        void setValue(std::string val);
        std::string getValue();
        std::string getPromt();
    };
}
