#include "MapParser.hpp"
#include <tinyxml.h>
#include "TileLayer.hpp"

namespace spic::internal
{
    MapParser::MapParser() : tileMap{}
    {}

    std::unique_ptr<TileMap> MapParser::Parse(const std::string filename)
    {
        TiXmlDocument xml;
        xml.LoadFile(filename);
        if (xml.Error()) {
            throw std::exception(xml.ErrorDesc());
        }

        TiXmlElement* root = xml.RootElement();
        root->Attribute("width", &colCount);
        root->Attribute("height", &rowCount);
        root->Attribute("tilewidth", &tileSize);

        // Parse Tilesets
        std::vector<TileSet> tilesets;
        for (TiXmlElement* element = root->FirstChildElement(); element != nullptr; element = element->NextSiblingElement())
        {
            if (element->Value() == std::string("tileset")) {
                tilesets.push_back(ParseTileSet(element));
                std::cout << element->Attribute("name") << " <-- Parsed!" << std::endl;
            }
        }

        // Parse Layers
        for (TiXmlElement* element = root->FirstChildElement(); element != nullptr; element = element->NextSiblingElement())
        {
            if (element->Value() == std::string("layer")) {
                ParseLayer(element, tilesets);
            }
        }
        return std::move(tileMap);
    }

    void MapParser::ParseLayer(TiXmlElement* tileLayerData, const std::vector<TileSet>& tilesets) {
        int layerIndex;
        tileLayerData->Attribute("id", &layerIndex);
        std::unique_ptr<TileLayer> tileLayer = std::make_unique<TileLayer>(layerIndex, tileSize, tilesets);
        Matrix matrix = ParseMatrix(tileLayerData);
        tileLayer->SetMatrix(matrix);
        tileMap->AddTileLayer(layerIndex, std::move(tileLayer));
    }

    Matrix MapParser::ParseMatrix(TiXmlElement* tileLayerData)
    {
        const TiXmlElement* data = nullptr;
        for (TiXmlElement* e = tileLayerData->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
            if (e->Value() == std::string("data"))
            {
                data = e;
                break;
            }
        }
        if (data == nullptr)
            throw std::exception("No matrix data");
        std::string dataString(data->GetText());
        std::istringstream iss(dataString);
        std::string tileId;

        Matrix matrix = Matrix(rowCount, std::vector<int>(colCount, 0));
        for (int row = 0; row < rowCount; row++)
        {
            for (int col = 0; col < colCount; col++)
            {
                getline(iss, tileId, ',');
                std::stringstream convertor(tileId);
                convertor >> matrix[row][col];

                if (!iss.good())
                    break;
            }
        }
        return matrix;
    }

    inline TileSet MapParser::ParseTileSet(TiXmlElement* tileSetData)
    {
        TileSet tileset;
        tileSetData->Attribute("firstgid", &tileset.firstId);
        tileSetData->Attribute("tilecount", &tileset.tileCount);
        tileset.lastId = (tileset.firstId + tileset.tileCount) - 1;
        tileSetData->Attribute("tilewidth", &tileset.tileSize);

        tileSetData->Attribute("columns", &tileset.columnCount);
        tileset.rowCount = static_cast<int>(tileset.tileCount / tileset.columnCount);

        TiXmlElement* image = tileSetData->FirstChildElement();
        std::string source = image->Attribute("source");
        return tileset;
    }
}