#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <string>
#include "TileLayer.hpp"
#include <map>

namespace spic::internal
{
	class TileMap
	{
	public:
		TileMap();
		void AddTileLayer(const int layer, const std::unique_ptr<TileLayer> tileLayer);
		const TileLayer& GetLayer(int index);
		void Render();
	private:
		std::map<int, std::unique_ptr<TileLayer>> tileLayers;
	};
}

#endif // TILEMAP_H_
