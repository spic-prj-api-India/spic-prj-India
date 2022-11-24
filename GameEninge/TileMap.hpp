#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <string>
#include <vector>
#include "TileLayer.hpp"

namespace spic::internal
{
	class TileMap
	{
	public:
		TileMap();
		void AddTileLayer(const std::unique_ptr<TileLayer>& tileLayer);
		const TileLayer& GetLayer(int index);
		inline void Render();
	private:
		std::vector<std::unique_ptr<TileLayer>> tileLayers;
	};
}

#endif // TILEMAP_H_
