#include "CastException.hpp"
#include <string>

namespace spic::internal::exceptions 
{
	CastException::CastException(const std::string castType) 
		: message{ "Extension has to be of type " + castType } 
	{
	}

	char* CastException::what() 
	{
		return (char*) message.c_str();
	}
}