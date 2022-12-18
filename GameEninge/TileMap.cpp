#include "TileMap.hpp"

namespace spic
{
	TileMap::TileMap(const int collisionLayerIndex)
	{
		this->collisionLayerIndex = collisionLayerIndex;
		tileLayers;
	}

	void TileMap::AddTileLayer(const int layerIndex, std::unique_ptr<TileLayer> tileLayer)
	{
		tileLayers[layerIndex] = std::move(tileLayer);
	}

	const TileLayer& TileMap::GetLayer(const int layerIndex) const
	{
		return *tileLayers.at(layerIndex);
	}

	const TileLayer& TileMap::GetCollisionLayer() const
	{
		return GetLayer(this->collisionLayerIndex);
	}

	void TileMap::Render() const
	{
		for (const auto& layer : tileLayers) layer.second->Render();
	}
}