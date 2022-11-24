#ifndef TILESET_H_
#define TILESET_H_

#include <string>

namespace spic::internal 
{
    struct TileSet
    {
        int rowCount, columnCount;
        int firstId, lastId;
        std::string textureId;
        int tileCount, tileSize;
    };
}

#endif // TILESET_H_
