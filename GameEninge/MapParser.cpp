#include "MapParser.hpp"
#include "TileMap.hpp"

namespace spic::internal
{
    MapParser::MapParser() 
    {}

    std::unique_ptr<TileMap> MapParser::Parse(const std::string filename)
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

        std::unique_ptr<TileMap> tileMap{};

        // Parse Tilesets
        std::vector<TileSet> tilesets;
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
                std::unique_ptr<TileLayer> layer = std::make_unique<TileLayer>(m_TileSize, tilesets);
                Matrix matrix = ParseMatrix(element, m_NbrRow, m_NbrCol);
                layer->SetMatrix(matrix);
                tileMap->AddTileLayer(std::move(layer));
                std::cout << element->Attribute("name") << " <-- Parsed!" << std::endl;
            }
        }

        std::cout << filename << " <-- Parsed!\n" << std::endl;
        return std::move(tileMap);
    }

    Matrix& MapParser::ParseMatrix(TiXmlElement* element, int rowCount, int columnCount)
    {
        const TiXmlElement* data;
        for (TiXmlElement* e = element->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
            if (e->Value() == std::string("data"))
            {
                data = e;
                break;
            }
        }

        std::string dataString(data->GetText());
        std::istringstream iss(dataString);
        std::string tileId;

        Matrix matrix = Matrix(rowCount, std::vector<int>(columnCount, 0));
        for (int row = 0; row < rowCount; row++)
        {
            for (int col = 0; col < columnCount; col++)
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

    inline TileSet& MapParser::ParseTileset(TiXmlElement* tileSetData)
    {
        TileSet tileset;
        tileset.textureId = tileSetData->Attribute("name");
        tileSetData->Attribute("firstgid", &tileset.firstId);
        tileSetData->Attribute("tilecount", &tileset.tileCount);
        tileset.lastId = (tileset.firstId + tileset.tileCount) - 1;
        tileSetData->Attribute("tilewidth", &tileset.tileSize);

        tileSetData->Attribute("columns", &tileset.columnCount);
        tileset.rowCount = static_cast<int>(tileset.tileCount / tileset.columnCount);
        return tileset;
    }

    void LoadTexture(TiXmlElement* tileSetData, const std::string& textureId)
    {
        TiXmlElement* image = tileSetData->FirstChildElement();
        std::string source = image->Attribute("source");
        std::unique_ptr<Sprite> sprite = std::make_unique<Sprite>();
        
    }
}