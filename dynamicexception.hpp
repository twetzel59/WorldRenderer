#ifndef CORE_DYNAMICEXCEPTION_HPP_INCLUDED
#define CORE_DYNAMICEXCEPTION_HPP_INCLUDED

#include <exception>
#include <string>

//For errors that vary in their message
// returned by what().

class DynamicException : public std::exception {
    private:
        std::string m_str;
    public:
        DynamicException(const std::string &msg) : m_str(msg) {}
        virtual ~DynamicException() {}

        virtual const char * what() const noexcept override final {
            return m_str.c_str();
        }
};

#endif // CORE_DYNAMICEXCEPTION_HPP_INCLUDED
