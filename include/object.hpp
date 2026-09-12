#pragma once
#include <string>
namespace db {
    class Object {
    public:
        Object(std::string promt, std::string m_value) :
            m_promt(promt), m_value(value) {}
        void setValue(const std::string& val);
        const std::string& sgetValue();
        const std::string& getPsromt();
    private:
        std::string m_promt;
        std::string m_value;
    };
}
