#include "TileLayer.hpp"
#include "Renderer.hpp"
#include "BoxCollider.hpp"
#include "EntityManager.hpp"

namespace spic::tiled
{
	TileLayer::TileLayer(const  int layerIndex, const int tilesize, const std::vector<TileSet> tilesets) :
		layerIndex{ layerIndex }, tileSize(tilesize), tilesets(tilesets)
	{
	}

	TileLayer::~TileLayer()
	{
		tileMatrix.clear();
		tileMatrix.shrink_to_fit();
		tilesets.clear();
		tilesets.shrink_to_fit();
	}

	void TileLayer::Render()
	{
		const Point size = GetSize();
		for (int rowIndex = 0; rowIndex < size.y; rowIndex++)
		{
			for (int colIndex = 0; colIndex < size.x; colIndex++)
			{
				int tileId = tileMatrix[colIndex][rowIndex];
				if (tileId == 0) continue;

				tileId--;
				TileSet& useTileset = tilesets[0];

				if (tilesets.size() > 1) {
					for (int tilesetIndex = 1; tilesetIndex < tilesets.size(); tilesetIndex++)
					{
						if (tileId >= (tilesets[tilesetIndex].firstId - 1) && tileId < tilesets[tilesetIndex].lastId)
						{
							tileId = tileId + tilesets[tilesetIndex].tileCount - tilesets[tilesetIndex].lastId;
							useTileset = tilesets[tilesetIndex];
							break;
						}
					}
				}

				const int tileRow = static_cast<int>(tileId / useTileset.columnCount);
				const int tileCol = static_cast<int>(tileId - (useTileset.columnCount * tileRow));

				std::unique_ptr<Sprite> sprite = GetSprite(useTileset, tileCol * tileSize, tileRow * tileSize, tileSize);
				const float x = static_cast<float>(colIndex * tileSize);
				const float y = static_cast<float>(rowIndex * tileSize);
				Transform transform = Transform(Point(x, y), 0.0f, 1.0f);
				spic::internal::Rendering::DrawSprite(transform, sprite.get());
			}
		}
	}

	std::unique_ptr<Sprite> TileLayer::GetSprite(const TileSet& tileSet, const int x, const int y, const int tileSize)
	{
		std::unique_ptr<Sprite> sprite = std::make_unique<Sprite>();
		sprite->_Sprite(tileSet.source);
		sprite->OrderInLayer(layerIndex);
		sprite->X(x);
		sprite->Y(y);
		sprite->Height(tileSize);
		sprite->Width(tileSize);
		return std::move(sprite);
	}

	void TileLayer::SetMatrix(const Matrix& matrix)
	{
		tileMatrix = matrix;
	}

	Matrix TileLayer::GetMatrix() const
	{
		return tileMatrix;
	}

	int TileLayer::GetTileSize() const
	{
		return tileSize;
	}

	Point TileLayer::GetSize() const
	{
		const float sizeX = static_cast<float>(tileMatrix.size());
		const float sizeY = static_cast<float>(tileMatrix[0].size());
		return Point(sizeX, sizeY);
	}
}