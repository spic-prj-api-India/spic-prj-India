#ifndef CASTEXCEPTION_H_
#define CASTEXCEPTION_H_

#include <iostream>

namespace spic::internal::exceptions {
    /**
     * @brief Throw this exception when class can not be casted to specific type
     */
    class CastException : public std::exception {
    public:
        /**
         * @brief Sets message, template: "Extension has to be of type {castType}"
         */
        CastException(const std::string castType);

        /**
         * @brief Returns error message
         */
        char* what();
    private:
        std::string message;
    };
}

#endif // CASTEXCEPTION_H_