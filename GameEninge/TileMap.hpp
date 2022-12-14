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
		TileMap(int collisionLayerIndex);

		/**
		 * @brief Adds tile layer
		 * @param layer Layer index.
		 * @param tileLayer TileLayer.
		 * @spicapi
		 */
		void AddTileLayer(const int layer, const std::unique_ptr<TileLayer> tileLayer);

		/**
		 * @brief Returns layer from list of layers using index.
		 * @param index Layer index.
		 * @return TileLayer.
		 * @spicapi
		 */
		const TileLayer& GetLayer(int index);

		/**
		 * @brief Returns collision layer.
		 * @return TileLayer.
		 * @spicapi
		 */
		const TileLayer& GetCollisionLayer();

		/**
		 * @brief Renders all tile layers.
		 * @spicapi
		 */
		void Render() const;
	private:
		std::map<int, std::unique_ptr<TileLayer>> tileLayers;
		std::vector<std::shared_ptr<spic::GameObject>> collisionEntities;
		int collisionLayerIndex;
	};
}

#endif // TILEMAP_H_
