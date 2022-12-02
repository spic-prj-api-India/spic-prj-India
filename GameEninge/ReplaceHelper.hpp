#ifndef REPLACEHELPER_H_
#define REPLACEHELPER_H_

#include <string>

namespace spic::internal {
    bool Replace(std::string& str, const std::string& from, const std::string& to) {
        size_t start_pos = str.find(from);
        if (start_pos == std::string::npos)
            return false;
        str.replace(start_pos, from.length(), to);
        return true;
    }
}

#endif // REPLACEHELPER_H_