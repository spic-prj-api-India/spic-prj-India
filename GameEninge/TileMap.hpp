#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <string>
#include "TileLayer.hpp"
#include <map>

namespace spic
{
	class TileMap
	{
	public:
		TileMap();
		void AddTileLayer(const int layer, const std::unique_ptr<TileLayer> tileLayer);
		const TileLayer& GetLayer(int index);
		void AddCollisionEntity(const std::shared_ptr<spic::GameObject> entity);
		std::vector<std::shared_ptr<spic::GameObject>>  CollisionEntities() const;
		void Render() const;
	private:
		std::map<int, std::unique_ptr<TileLayer>> tileLayers;
		std::vector<std::shared_ptr<spic::GameObject>> collisionEntities;
	};
}

#endif // TILEMAP_H_
