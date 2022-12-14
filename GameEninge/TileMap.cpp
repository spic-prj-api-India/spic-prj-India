#include "TileMap.hpp"

namespace spic
{
	TileMap::TileMap(int collisionLayerIndex)
	{
		this->collisionLayerIndex = collisionLayerIndex;
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

	const TileLayer& TileMap::GetCollisionLayer()
	{
		return GetLayer(this->collisionLayerIndex);
	}

	void TileMap::Render() const
	{
		for (const auto& layer : tileLayers) layer.second->Render();
	}
}