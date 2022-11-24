#ifndef MAPPARSER_H_
#define MAPPARSER_H_

#include <vector>
#include <string>
#include <tinyxml.h>
#include "TileMap.hpp"

namespace spic::internal
{
    class MapParser
    {
    public:
        MapParser();
        std::unique_ptr<TileMap> Parse(const std::string filename);
    private:
        void ParseLayer(TiXmlElement* tileLayerData, const std::vector<TileSet>& tilesets);
        Matrix ParseMatrix(TiXmlElement* tileLayerData);
        inline TileSet ParseTileSet(TiXmlElement* tileSetData);
    private:
        int tileSize, rowCount, colCount;
        std::unique_ptr<TileMap> tileMap;
    };
}

#endif // MAPPARSER_H_