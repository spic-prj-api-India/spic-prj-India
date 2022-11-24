#pragma once

#include <vector>
#include <string>
#include <tinyxml.h>
#include "TileLayer.hpp"

namespace spic::internal
{
    class MapParser
    {
    public:
        MapParser();
        std::unique_ptr<TileMap> Parse(const std::string filename);
    private:
        Matrix& ParseMatrix(TiXmlElement* element, int rowCount, int columnCount);
        inline TileSet& ParseTileset(TiXmlElement* element);
    private:
        int m_TileSize, m_NbrCol, m_NbrRow;
    };
}