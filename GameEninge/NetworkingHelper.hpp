#ifndef NETWORKINGHELPER_H_
#define NETWORKINGHELPER_H_

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

/**
 * @brief Contains helpfull preprogrammed functions
*/
namespace spic::helper_functions
{
    /**
     * @brief Contains hulpfull network helper(s)
    */
    namespace networking_helper
    {
        /**
         * @brief Gets parsed info from ipconfig commands (windows only)
         * @details To get ip4 address use "IPv4 Address" as parameter
         * @param Columb Which parameter you want
         * @return Your private ip address
        */
        std::string GetParsedIPConfigData(const std::string& Columb);
    }
};
#endif