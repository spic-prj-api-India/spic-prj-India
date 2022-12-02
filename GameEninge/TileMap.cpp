#include "TileMap.hpp"

namespace spic
{
	TileMap::TileMap()
	{
		tileLayers;
	}

	void TileMap::AddTileLayer(const int layerIndex, std::unique_ptr<TileLayer> tileLayer)
	{
		tileLayers[layerIndex] = std::move(tileLayer);
	}

	const TileLayer& TileMap::GetLayer(int layerIndex)
	{
		return *tileLayers[layerIndex];
	}

	void TileMap::AddCollisionEntity(const std::shared_ptr<spic::GameObject> entity) {
		collisionEntities.emplace_back(entity);
	}

	std::vector<std::shared_ptr<spic::GameObject>> TileMap::CollisionEntities() {
		return collisionEntities;
	}

	void TileMap::Render()
	{
		for (const auto& layer : tileLayers) layer.second->Render();
	}
}