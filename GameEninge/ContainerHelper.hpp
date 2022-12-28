#ifndef CONTAINERHELPER_H_
#define CONTAINERHELPER_H_

#include <map>
#include <vector>
#include <functional>
#include "TypeHelper.hpp"

/**
 * @brief Contains helpfull preprogrammed functions
*/
namespace spic::helper_functions
{
	/**
	 * @brief Contains methods which can convert an map to an vector
	*/
	namespace container
	{
        /**
         * @brief Function that is used for finding object in container. 
         *          Format: [](std::shared_ptr<T>){return true}
         * @tparam T 
        */
        template <typename T>
        using FindFunction = std::function<bool(std::shared_ptr<T>)>;

		/**
		* @brief Converts map to vector with keys.
		* @tparam K Can be any value.
		* @tparam V Can be any value.
		* @param map
		* @return
		*/
		template <typename K, typename V>
		std::vector<K> GetKeys(std::map<K, V> map) {
			std::vector<K> keys;
			for (const auto& keypair : map) {
				keys.emplace_back(keypair.first);
			}
			return keys;
		}

        /**
         * @brief Converts map to list with values.
         * @tparam K Can be any value.
         * @tparam V Can be any value.
         * @param map Map with keyvalue pairs.
         * @return Vector of values.
        */
        template <typename K, typename V>
        std::vector<V> GetValues(std::map<K, V> map) {
            std::vector<V> values;
            for (const auto& keypair : map) {
                values.emplace_back(keypair.second);
            }
            return values;
        }

        /**
         * @brief Finds element in vector with find function
         * @param vector Vector to search in
         * @param findFunction Lambda function that checks if element is right element
         *          Format: [](std::shared_ptr<T>){return true}
         * @return shared_ptr or nullptr
        */
        template <typename T>
        std::shared_ptr<T> Find(const std::vector<std::shared_ptr<T>>& vector, FindFunction<T> findFunction) 
        {
            auto it = find_if(vector.begin(), vector.end(), [&findFunction](std::shared_ptr<T> element) 
            {
                return findFunction(element);
                });

            if (it == vector.end())
                return nullptr;

            auto index = std::distance(vector.begin(), it);
            return vector[index];
        }

        /**
         * @brief Finds element in vector with find function and converts element to given type
         * @param vector Vector to search in
         * @param findFunction Lambda function that checks if element is right element
         *          Format: [](std::shared_ptr<T>){return true}
         * @return shared_ptr or nullptr
        */
        template <typename T, typename C>
        std::shared_ptr<C> FindAndConvert(const std::vector<std::shared_ptr<T>>& vector, FindFunction<T> findFunction) 
        {
            auto it = find_if(vector.begin(), vector.end(), [&findFunction](std::shared_ptr<T> element) 
            {
                return findFunction(element);
                });

            if (it == vector.end())
                return nullptr;

            auto index = std::distance(vector.begin(), it);
            return helper_functions::type_helper::CastSharedPtrToType<C>(vector[index]);
        }
    }
}

#endif // CONTAINERHELPER_H_