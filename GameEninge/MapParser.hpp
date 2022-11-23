#ifndef MAPPARSER_H_
#define MAPPARSER_H_

#include <vector>
#include <string>
#include <tinyxml.h>
#include "TileLayer.hpp"

namespace spic
{

    class MapParser
    {

    public:
        MapParser() {}

        virtual ~MapParser()
        {
            m_Layers.clear();
            m_Layers.shrink_to_fit();
        }

        void Render()
        {
            for (auto layer : m_Layers) layer->Render();
        }

        void Update(float delta)
        {
            for (auto layer : m_Layers) layer->Update(delta);
        }

        void Parse(const std::string filename)
        {
            TiXmlDocument xml;
            xml.LoadFile(filename);
            if (xml.Error()) {
                std::cout << xml.ErrorDesc() << std::endl;
                return;
            }

            TiXmlElement* root = xml.RootElement();
            root->Attribute("width", &m_NbrCol);
            root->Attribute("height", &m_NbrRow);
            root->Attribute("tilewidth", &m_TileSize);

            // Parse Tilesets
            std::vector<Tileset> tilesets;
            for (TiXmlElement* element = root->FirstChildElement(); element != nullptr; element = element->NextSiblingElement())
            {
                if (element->Value() == std::string("tileset")) {
                    tilesets.push_back(ParseTileset(element));
                    std::cout << element->Attribute("name") << " <-- Parsed!" << std::endl;
                }
            }

            // Parse Layers
            for (TiXmlElement* element = root->FirstChildElement(); element != nullptr; element = element->NextSiblingElement())
            {
                if (element->Value() == std::string("layer")) {
                    TileLayer* layer = new TileLayer(m_TileSize, tilesets);
                    layer->ParseTileMatrix(element, m_NbrRow, m_NbrCol);
                    m_Layers.push_back(layer);
                    std::cout << element->Attribute("name") << " <-- Parsed!" << std::endl;
                }
            }

            std::cout << filename << " <-- Parsed!\n" << std::endl;
        }

        TileLayer* GetLayer(int index) {
            return m_Layers[index];
        }

    private:
        inline Tileset ParseTileset(TiXmlElement* element)
        {
            Tileset tileset;
            tileset.textureId = element->Attribute("name");
            element->Attribute("firstgid", &tileset.firstId);
            element->Attribute("tilecount", &tileset.tileCount);
            tileset.lastId = (tileset.firstId + tileset.tileCount) - 1;
            element->Attribute("tilewidth", &tileset.tileSize);

            element->Attribute("columns", &tileset.columnCount);
            tileset.rowCount = static_cast<int>(tileset.tileCount / tileset.columnCount);
            return tileset;
        }

    private:
        std::vector<TileLayer*> m_Layers;
        int m_TileSize, m_NbrCol, m_NbrRow;
    };
}

#endif // MAPPARSER_H_