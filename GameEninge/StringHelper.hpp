#ifndef REPLACEHELPER_H_
#define REPLACEHELPER_H_

#include <string>

namespace spic::StringHelper {
    bool Replace(std::string& str, const std::string& from, const std::string& to);

    std::string GetBasePath();
}

#endif // REPLACEHELPER_H_