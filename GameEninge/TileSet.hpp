#ifndef TILESET_H_
#define TILESET_H_

#include <string>

namespace spic 
{
    /**
     * @brief Contains all tiled related classes
    */
    namespace tiled
    {
        /**
         * @brief An struct which contains what an TileSet needs
        */
        struct TileSet
        {
            int rowCount, columnCount;
            int firstId, lastId;
            std::string source;
            int tileCount, tileSize;
        };
    }
}

#endif // TILESET_H_
