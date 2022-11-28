#ifndef TILESET_H_
#define TILESET_H_

#include <string>

namespace spic 
{
    struct TileSet
    {
        int rowCount, columnCount;
        int firstId, lastId;
        std::string source;
        int tileCount, tileSize;
    };
}

#endif // TILESET_H_
