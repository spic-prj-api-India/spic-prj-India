#ifndef CONTAINERHELPER_H_
#define CONTAINERHELPER_H_

#include <map>
#include <vector>
#include <functional>

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

	template <typename T>
	std::shared_ptr<T> Find(const std::vector<std::shared_ptr<T>>& vector, std::function<bool(std::shared_ptr<T>)> findFunction) {
		auto it = find_if(vector.begin(), vector.end(), [&findFunction](std::shared_ptr<T> element) {
			return findFunction(element);
			});

		if (it == vector.end())
			return nullptr;

		auto index = std::distance(vector.begin(), it);
		return vector[index];
	}
}

#endif // CONTAINERHELPER_H_