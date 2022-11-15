#pragma once

#include <string>
#include <vector>
#include <tinyxml.h>
#include <iostream>

namespace spic
{

    using Matrix = std::vector<std::vector<int> >;

    struct Tileset
    {
        int rowCount, columnCount;
        int firstId, lastId;
        std::string textureId;
        int tileCount, tileSize;
    };

    class TileLayer
    {

    public:
        TileLayer(const int tilesize, const std::vector<Tileset> tilesets) : tileSize(tilesize), tilesets(tilesets) {}

        virtual ~TileLayer()
        {
            tileMatrix.clear();
            tileMatrix.shrink_to_fit();
            tilesets.clear();
            tilesets.shrink_to_fit();
        }

        inline void Render()
        {
        }

        inline void Update(float delta)
        {

        }

        inline void ParseTileMatrix(TiXmlElement* element, int rowCount, int columnCount)
        {
        }

        inline Matrix GetMatrix() const
        {
            return tileMatrix;
        }

        inline int GetTilesize() const
        {
            return tileSize;
        }

        inline int GetSize() const
        {
        }

    private:
        int tileSize;
        Matrix tileMatrix;
        std::vector<Tileset> tilesets;
    };
}