#include "TileMap.hpp"

namespace spic::internal
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

	void TileMap::Render()
	{
		for (const auto& layer : tileLayers) layer.second->Render();
	}
}