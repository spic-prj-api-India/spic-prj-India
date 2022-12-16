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
        /**
         * @param collisionLayerIndex Index of layer where collision tiles are.
         */
        MapParser(const int collisionLayerIndex);

        /**
         * @brief Parse tmx file to Tilemap.
         * @param fileName File name of tmx file.
         * @spicapi
         */
        std::unique_ptr<spic::TileMap> Parse(const std::string fileName);
    private:
        /**
         * @brief Parse tile layer and add layer to tile map.
         * @param tileLayerData Tile layer data from tmx file.
         * @param tilesets Converted tilesets from tmx file.
         * @return layer index.
         * @spicapi
         */
        int ParseLayer(const TiXmlElement& tileLayerData, const std::vector<spic::TileSet>& tilesets);

        /**
         * @brief Parse tile matrix.
         * @param tileLayerData Tile layer data from tmx file.
         * @return Matrix
         * @spicapi
         */
        spic::Matrix ParseMatrix(const TiXmlElement& tileLayerData);

        /**
         * @brief Parse tile set.
         * @param tileSetData Tile set data from tmx file.
         * @return TileSet
         * @spicapi
         */
        spic::TileSet ParseTileSet(const TiXmlElement& tileSetData);

        /**
         * @brief Creates collision entities with layer and tilesets.
         * @param collisionLayerIndex Collision layer index.
         * @param tilesets Tilesets.
         * @spicapi
         */
        void CreateCollisionEntities(const int collisionLayerIndex, const std::vector<TileSet>& tilesets);

        /**
         * @brief Creates entity with tile data and adds to tile map.
         * @param collisionLayerIndex Collision layer index.
         * @param tilesets Tilesets.
         * @spicapi
         */
        void CreateEntity(const float x, const float y, const std::string& name, int tileSize) const;
    private:
        int tileSize, rowCount, colCount;
        std::unique_ptr<spic::TileMap> tileMap;
    };
}

#endif // MAPPARSER_H_