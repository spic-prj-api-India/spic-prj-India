#ifndef PERSISTABLE_H_
#define PERSISTABLE_H_

#include "GameObject.hpp"
#include <map>
#include <functional>

namespace spic 
{
	/**
	 * @brief Makes a GameObject persistable, so that it can be loaded back in later on.
	 */
	class Persistable
	{
	public:
		/**
		 * @brief Makes a GameObject persistable, so that it can be loaded back in later on.
		 * @param gameObject The GameObject te make persistable.
		 * @param typeName The type of the GameObject.
		 */
		Persistable(GameObject* gameObject, std::string typeName);
		virtual ~Persistable() = default;
		Persistable(const Persistable& other) = delete;
		Persistable(Persistable&& other) = delete;
		Persistable& operator=(const Persistable& other) = delete;
		Persistable& operator=(Persistable&& other) = delete;

		/**
		 * @brief Saves the properties of the GameObject.
		 * @return A map containing the properties of the GameObject, or an empty map if the GameObject is nullptr.
		 */
		virtual std::map<std::string, std::function<std::string()>> SaveProperties();
		
		/**
		 * @brief Loads the properties of the GameObject.
		 * @return A map used for passing the properties of the GameObject, which are then set to the GameObject. Or an empty map if the GameObject is nullptr.
		 */
		virtual std::map<std::string, std::function<void(const std::string&)>> LoadProperties();
	private:
		/**
		* @brief The GameObject to make persistable.
		*/
		GameObject* gameObject;
		
		/**
		* @brief The Type of the GameObject.
		*/
		std::string typeName;
	};
}
#endif // PERSISTABLE_H_