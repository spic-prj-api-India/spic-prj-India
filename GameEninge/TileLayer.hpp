#ifndef TILELAYER_H_
#define TILELAYER_H_

#include <vector>
#include "TileSet.hpp"
#include "Point.hpp"
#include "Sprite.hpp"

namespace spic
{
    /**
     * @brief Contains all tiled related classes
    */
    namespace tiled
    {
        /**
         * @brief Using mask named Matrix for vector with vector<int>
        */
        using Matrix = std::vector<std::vector<int>>;

        /**
         * @brief Defines a tilelayer (from Tiled)
        */
        class TileLayer
        {
        public:

            /**
             * @brief Constructor
             * @param layerIndex The layer index for this layer
             * @param tilesize The size in pixels of 1 tile
             * @param tilesets All TileSet objects of this layer
            */
            TileLayer(const int layerIndex, const int tilesize, const std::vector<TileSet> tilesets);

            virtual ~TileLayer();

            /**
            * @brief Renders the tile layer
            */
            void Render();

            /**
            * @brief Sets matrix of Tilelayer.
            * @param matrix Desired new matrix.
            */
            void SetMatrix(const Matrix& matrix);

            /**
             * @brief Getter
             * @return Returns matrix of Tilelayer (see allias).
             */
            Matrix GetMatrix() const;

            /**
             * @brief Getter
             * @return tileSize
            */
            int GetTileSize() const;

            /**
             * @brief Getter
             * @return An Point which contains the collum and row size [row, collum].
             */
            Point GetSize() const;
        private:

            /**
             * @brief Creates an sprite based on the informatation given
             * @param tileSet Contains the sprite texture
             * @param x Sets the x coordinate of the sprite
             * @param y Sets the y coordinate of the sprite
             * @param tileSize The size 
             * @return Unique_ptr which contains an Sprite object
            */
            std::unique_ptr<Sprite> GetSprite(const TileSet& tileSet, const int x, const int y, const int tileSize);
        private:

            /**
             * @brief The size in pixels of 1 tile in this tileLayer
            */
            int tileSize;
            int layerIndex;
            Matrix tileMatrix;
            std::vector<TileSet> tilesets;
        };
    }
}

#endif // TILELAYER_H_