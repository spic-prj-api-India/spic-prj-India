#ifndef CASTEXCEPTION_H_
#define CASTEXCEPTION_H_

#include <iostream>

namespace spic {
    class CastException : public std::exception {
    public:
        CastException(std::string castType);
        char* what();
    private:
        std::string message;
    };
}

#endif // CASTEXCEPTION_H_