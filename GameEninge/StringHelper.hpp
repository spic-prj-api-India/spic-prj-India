#ifndef STRINGHELPER_H_
#define STRINGHELPER_H_

#include <string>

namespace spic::StringHelper {
    /**
     * @brief Replaces certain string in string with other string
     * @param str Base string.
     * @param from String that needs to be replaced.
     * @param to Replacement string.
     * @return bool
     * @spicapi
     */
    bool Replace(std::string& str, const std::string& from, const std::string& to);

    /**
    * @brief Gets base path of engine
    * @spicapi
    */
    std::string GetBasePath();
}

#endif // STRINGHELPER_H_