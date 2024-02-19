#ifndef PFLOOP_SRC_ARGUMENTS_BAD_FILE_EXCEPTION_H
#define PFLOOP_SRC_ARGUMENTS_BAD_FILE_EXCEPTION_H

#include <stdexcept>

class BadFileException : public std::exception
{                             
public:
    BadFileException(const char* t_message)
        : m_errorMessage(t_message) {}
    
    const char* what() const noexcept override {
        return m_errorMessage.c_str();
    }
    
private:
    std::string m_errorMessage;
};

#endif // PFLOOP_SRC_ARGUMENTS_BAD_FILE_EXCEPTION_H
