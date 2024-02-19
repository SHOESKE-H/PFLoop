#ifndef PFLOOP_SRC_ARGUMENTS_EXPECTED_ARGUMENT_EXCEPTION_H
#define PFLOOP_SRC_ARGUMENTS_EXPECTED_ARGUMENT_EXCEPTION_H

#include <stdexcept>

class ExpectedArgumentException : public std::exception
{
public:
    ExpectedArgumentException(const char* t_message)
        : m_errorMessage(t_message) {}

    const char* what() const noexcept override
    {
        return m_errorMessage.c_str();
    }

private:
    std::string m_errorMessage;
};

#endif // PFLOOP_SRC_ARGUMENTS_EXPECTED_ARGUMNET_EXCEPTION_H
