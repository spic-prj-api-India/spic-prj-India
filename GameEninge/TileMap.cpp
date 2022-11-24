#include "TileMap.hpp"

namespace spic::internal
{
	TileMap::TileMap() : tileLayers{}
	{}

	void TileMap::AddTileLayer(const std::unique_ptr<TileLayer>& tileLayer)
	{
		tileLayers.emplace_back(std::move(tileLayer));
	}

	const TileLayer& TileMap::GetLayer(int index)
	{
		return *tileLayers[index];
	}

	void TileMap::Render()
	{
		for (const auto& layer : tileLayers) layer->Render();
	}
}