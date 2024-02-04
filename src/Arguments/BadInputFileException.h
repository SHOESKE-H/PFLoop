#include <stdexcept>

class BadInputFileException : public std::exception
{                             
public:
    BadInputFileException(const char* message)
        : errorMessage(message) {}
    
    const char* what() const noexcept override {
        return errorMessage.c_str();
    }   
    
private:
    std::string errorMessage;
};  
