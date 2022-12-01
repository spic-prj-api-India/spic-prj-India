#ifndef STRINGHELPER_H_
#define STRINGHELPER_H_

#include <string>

namespace spic::StringHelper {
    bool Replace(std::string& str, const std::string& from, const std::string& to);

    std::string GetBasePath();
}

#endif // STRINGHELPER_H_