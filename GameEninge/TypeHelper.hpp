#ifndef TYPEHELPER_H_
#define TYPEHELPER_H_

#include <string>
#include <regex>

namespace spic::internal {
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
}

#endif // TYPEHELPER_H_