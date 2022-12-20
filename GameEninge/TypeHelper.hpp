#ifndef TYPEHELPER_H_
#define TYPEHELPER_H_

#include <string>
#include <regex>
#include <memory>

/**
 * @brief Contains helpfull preprogrammed functions
*/
namespace spic::helper_functions
{
	/**
	 * @brief Contains helpfull type functions
	*/
	namespace type_helper
	{
		/**
		 * @brief Gets name of type
		 * @tparam T The type to get the name of
		 * @return The name of object T
		 */
		template <typename T>
		std::string GetTypeName()
		{
			std::string typeName = typeid(T).name();
			std::string strippedName = std::regex_replace(typeName, std::regex("class "), "");
			return strippedName;
		}

		/**
		 * @brief Gets name of object
		 * @tparam T The object to get the name of
		 * @param object An object
		 * @return THe string name of object T
		*/
		template <typename T>
		std::string GetTypeName(T object)
		{
			std::string typeName = typeid(object).name();
			std::string strippedName = std::regex_replace(typeName, std::regex("class "), "");
			return strippedName;
		}

		/**
		 * @brief  Checks if shared ptr is from type T (base class)
		 * @tparam T A base class
		 * @tparam P A derived or base class
		 * @param pointer The shared_ptr
		 * @return If it is of type T
		*/
		template <typename T, typename P>
		bool SharedPtrIsOfType(std::shared_ptr<P> pointer)
		{
			return std::dynamic_pointer_cast<T>(pointer) != nullptr;
		}

		/**
		 * @brief Try's to cast a shared_ptr pointer to another pointer
		 * @tparam T A Base class
		 * @tparam P A derived or base class
		 * @param pointer The shared_ptr
		 * @return A shared_ptr of type T or a nullptr
		*/
		template <typename T, typename P>
		std::shared_ptr<T> CastSharedPtrToType(std::shared_ptr<P> pointer)
		{
			return std::dynamic_pointer_cast<T>(pointer);
		}

		/**
		 * @brief Try's to cast a pointer to weak pointer
		 * @tparam T A Base class
		 * @tparam P A derived or base class
		 * @param pointer An pointer
		 * @return A pointer of type T or a nullptr
		* @spicapi
		*/
		template <typename T, typename P>
		std::weak_ptr<T> CastSharedPtrToWeakType(std::shared_ptr<P> pointer)
		{
			return std::dynamic_pointer_cast<T>(pointer);
		}

		/**
		 * @brief Casts ptr to certain type
		 * @tparam T A Base class
		 * @tparam P A derived or base class
		 * @param pointer An pointer
		 * @return A pointer of type T or a nullptr
		 * @spicapi
		*/
		template <typename T, typename P>
		T* CastPtrToType(P* pointer)
		{
			return static_cast<T*>(pointer);
		}
	}
}

#endif // TYPEHELPER_H_