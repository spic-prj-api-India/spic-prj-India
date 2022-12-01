#ifndef CONTAINERHELPER_H_
#define CONTAINERHELPER_H_

#include <map>
#include <vector>

namespace spic::ContainerHelper {
    /**
    * @brief Converts map to list with keys.
    * @param map Map with keyvalue pairs.
    * @return list of keys
    * @spicapi
    */
    template <typename K, typename V>
    std::vector<K> GetKeys(std::map<K, V> map) {
        std::vector<K> keys;
        for (const auto& keypair : map) {
            keys.emplace_back(keypair.first);
        }
        return keys;
    }
}

#endif // CONTAINERHELPER_H_