#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <string>
#include "TileLayer.hpp"
#include <map>

namespace spic
{
	/**
	 * @brief Contains all tiled related classes
	*/
	namespace tiled
	{
		/**
		 * @brief An object which contains all TileLayers and 
		*/
		class TileMap
		{
		public:
			/**
			 * @brief Constructor
			 * @param collisionLayerIndex Which layer it collisions with
			*/
			TileMap(const int collisionLayerIndex);

			/**
			 * @brief Adds an tile layer to the map
			 * @param layer Layer index of the layer
			 * @param tileLayer An unique_ptr TileLayer object
			 * @spicapi
			 */
			void AddTileLayer(const int layer, const std::unique_ptr<TileLayer> tileLayer);

			/**
			 * @brief Returns an collision layer based on the index
			 * @param index Layer index.
			 * @return TileLayer.
			 */
			const TileLayer& GetLayer(const int index) const;

			/**
			 * @brief Returns an collision layer based on the current collisionLayerIndex.
			 * @return TileLayer.
			 */
			const TileLayer& GetCollisionLayer() const;

			/**
			 * @brief Renders all tile layers.
			 */
			void Render() const;
		private:
			std::map<int, std::unique_ptr<TileLayer>> tileLayers;
			int collisionLayerIndex;
		};
	}
}

#endif // TILEMAP_H_
