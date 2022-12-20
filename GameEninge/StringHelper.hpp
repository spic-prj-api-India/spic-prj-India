#ifndef STRINGHELPER_H_
#define STRINGHELPER_H_

#include <string>

/**
 * @brief Contains helpfull preprogrammed functions
*/
namespace spic::helper_functions
{
    /**
     * @brief Contains helpfull string functions
    */
    namespace string_helper
    {
        /**
         * @brief Replaces certain string in string with other string
         * @param str Base string.
         * @param from String that needs to be replaced.
         * @param to Replacement string.
         * @return bool If it has succeeded
         */
        bool Replace(std::string& str, const std::string& from, const std::string& to);

        /**
        * @brief Gets base path of engine (only usefull in develop cause it points to source code folder)
        */
        std::string GetBasePath();
    }
}

#endif // STRINGHELPER_H_