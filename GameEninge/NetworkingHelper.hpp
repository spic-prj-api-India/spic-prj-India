#ifndef NETWORKINGHELPER_H_
#define NETWORKINGHELPER_H_

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

namespace spic::networkingHelper
{

    /**
     * @brief Gets parsed info from ipconfig commands (windows only)
     * @details to get ip4 address use "IPv4 Address" as parameter
     * @param Columb Which parameter you want
     * @return 
    */
    std::string GetParsedIPConfigData(const std::string& Columb);
   
};
#endif