#include "StringHelper.hpp"

bool spic::StringHelper::Replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);

	if (start_pos == std::string::npos)
		return false;

	str.replace(start_pos, from.length(), to);
	return true;
}

std::string  spic::StringHelper::GetBasePath()
{
	std::string filePath = __FILE__;
	std::string searchFor = "GameEninge";
	size_t pos = filePath.find(searchFor) + searchFor.length();
	return filePath.erase(pos, filePath.length() - pos);
}