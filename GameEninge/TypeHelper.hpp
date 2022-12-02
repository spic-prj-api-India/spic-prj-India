#ifndef TYPEHELPER_H_
#define TYPEHELPER_H_

#include <string>
#include <regex>

namespace spic {
	/**
	* @brief Gets name of type
	* @spicapi
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
	* @spicapi
	*/
	template <typename T>
	std::string GetTypeName(T object)
	{
		std::string typeName = typeid(object).name();
		std::string strippedName = std::regex_replace(typeName, std::regex("class "), "");
		return strippedName;
	}

	/**
	* @brief Checks if shared ptr is of type
	* @spicapi
	*/
	template <typename T, typename P>
	bool SharedPtrIsOfType(std::shared_ptr<P> pointer)
	{
		return std::dynamic_pointer_cast<T>(pointer) != nullptr;
	}

	/**
	* @brief Casts shared ptr to certain type
	* @spicapi
	*/
	template <typename T, typename P>
	std::shared_ptr<T> CastSharedPtrToType(std::shared_ptr<P> pointer)
	{
		return std::dynamic_pointer_cast<T>(pointer);
	}

	/**
	* @brief Casts ptr to certain type
	* @spicapi
	*/
	template <typename T, typename P>
	T* CastPtrToType(P* pointer)
	{
		return static_cast<T*>(pointer);
	}
}

#endif // TYPEHELPER_H_