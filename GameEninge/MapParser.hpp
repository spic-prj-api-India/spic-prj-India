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
        std::unique_ptr<spic::TileMap> Parse(const std::string filename, const int collisionLayerIndex);
    private:
        int ParseLayer(const TiXmlElement& tileLayerData, const std::vector<spic::TileSet>& tilesets);
        spic::Matrix ParseMatrix(const TiXmlElement& tileLayerData);
        inline spic::TileSet ParseTileSet(const TiXmlElement& tileSetData);
        void CreateCollisionEntities(const int collisionLayerIndex, const std::vector<TileSet>& tilesets);
        void CreateEntity(const float x, const float y, const std::string& name, int tileSize) const;
    private:
        int tileSize, rowCount, colCount;
        std::unique_ptr<spic::TileMap> tileMap;
    };
}

#endif // MAPPARSER_H_