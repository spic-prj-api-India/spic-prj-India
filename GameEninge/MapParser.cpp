#include "MapParser.hpp"
#include "TileLayer.hpp"
#include "ReplaceHelper.hpp"
#include "BoxCollider.hpp"
#include "EntityManager.hpp"

namespace spic::internal
{
	MapParser::MapParser()
	{
		tileMap = std::make_unique<TileMap>();
	}

	std::unique_ptr<TileMap> MapParser::Parse(const std::string filename, const int collisionLayerIndex)
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
		for (const TiXmlElement* element = root->FirstChildElement(); element != nullptr; element = element->NextSiblingElement())
		{
			if (element->Value() == std::string("tileset")) {
				tilesets.push_back(ParseTileSet(*element));
				std::cout << element->Attribute("name") << " <-- Parsed!" << std::endl;
			}
		}

		// Parse Layers
		for (const TiXmlElement* element = root->FirstChildElement(); element != nullptr; element = element->NextSiblingElement())
		{
			if (element->Value() == std::string("layer")) {
				if (ParseLayer(*element, tilesets) == collisionLayerIndex) {
					CreateCollisionEntities(collisionLayerIndex, tilesets);
				}
			}
		}
		return std::move(tileMap);
	}

	int MapParser::ParseLayer(const TiXmlElement& tileLayerData, const std::vector<TileSet>& tilesets) {
		int layerIndex;
		tileLayerData.Attribute("id", &layerIndex);
		std::unique_ptr<TileLayer> tileLayer = std::make_unique<TileLayer>(layerIndex, tileSize, tilesets);
		Matrix matrix = ParseMatrix(tileLayerData);
		tileLayer->SetMatrix(matrix);
		tileMap->AddTileLayer(layerIndex, std::move(tileLayer));
		return layerIndex;
	}

	Matrix MapParser::ParseMatrix(const TiXmlElement& tileLayerData)
	{
		const TiXmlElement* data = nullptr;
		for (const TiXmlElement* e = tileLayerData.FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
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

	inline TileSet MapParser::ParseTileSet(const TiXmlElement& tileSetData)
	{
		TileSet tileset;
		tileSetData.Attribute("firstgid", &tileset.firstId);
		tileSetData.Attribute("tilecount", &tileset.tileCount);
		tileset.lastId = (tileset.firstId + tileset.tileCount) - 1;
		tileSetData.Attribute("tilewidth", &tileset.tileSize);

		tileSetData.Attribute("columns", &tileset.columnCount);
		tileset.rowCount = static_cast<int>(tileset.tileCount / tileset.columnCount);

		const TiXmlElement& image = *tileSetData.FirstChildElement();
		tileset.source = image.Attribute("source");
		Replace(tileset.source, "..", "assets");
		return tileset;
	}

	void MapParser::CreateCollisionEntities(const int collisionLayerIndex, const std::vector<TileSet>& tilesets) {
		const TileLayer& layer = tileMap->GetLayer(collisionLayerIndex);
		const Matrix& matrix = layer.GetMatrix();
		for (unsigned int i = 0; i < matrix.size(); i++)
		{
			for (unsigned int j = 0; j < matrix[1].size(); j++)
			{
				int tileId = matrix[i][j];
				if (tileId == 0) continue;

				else {
					tileId--;
					int tilesetIndex = 0;

					if (tilesets.size() > 1) {
						for (unsigned int k = 1; k < tilesets.size(); k++)
						{
							if (tileId >= (tilesets[k].firstId - 1) && tileId < tilesets[k].lastId)
							{
								tileId = tileId + tilesets[k].tileCount - tilesets[k].lastId;
								tilesetIndex = k;
								break;
							}
						}
					}

					const int tileRow = static_cast<int>(tileId / tilesets[tilesetIndex].columnCount);
					const int tileCol = static_cast<int>(tileId - (tilesets[tilesetIndex].columnCount * tileRow));
					const float x = static_cast<float>(j * tileSize);
					const float y = static_cast<float>(i * tileSize);

					CreateEntity(x, y, "tile" + std::to_string(j) + std::to_string(i), layer.GetTilesize());
				}
			}
		}
	}

	void MapParser::CreateEntity(const float x, const float y, const std::string& name, int tileSize) const {
		std::shared_ptr<spic::GameObject> entity = std::make_shared<spic::GameObject>();
		std::string tag = "tilemap";
		std::shared_ptr<spic::Transform> transform = std::make_shared<spic::Transform>();
		transform->position = { x, y };
		transform->rotation = 0.0f;
		transform->scale = 1.0f;
		std::shared_ptr<spic::BoxCollider> boxCollider = std::make_shared<spic::BoxCollider>();
		boxCollider->Width(static_cast<float>(tileSize));
		boxCollider->Height(static_cast<float>(tileSize));
		std::shared_ptr<spic::RigidBody> rigidBody = std::make_shared<spic::RigidBody>(1.0f, 0.0f, spic::BodyType::staticBody);

		entity->Tag(tag);
		entity->Name(name);
		entity->Transform(transform);
		entity->AddComponent<spic::BoxCollider>(boxCollider);
		entity->AddComponent<spic::RigidBody>(rigidBody);

		tileMap->AddCollisionEntity(entity);
	}
}