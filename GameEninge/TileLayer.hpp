#ifndef TILELAYER_H_
#define TILELAYER_H_

#include <vector>
#include <iostream>
#include "TileSet.hpp"
#include "Point.hpp"
#include "GameObject.hpp"

namespace spic
{
    using Matrix = std::vector<std::vector<int>>;

    class TileLayer
    {
    public:
        TileLayer(const int layerIndex, const int tilesize, const std::vector<TileSet> tilesets);

        virtual ~TileLayer();

        /**
        * @brief Renders tile layer with Renderer
        * @spicapi
        */
        void Render();

        /**
        * @brief Sets matrix of Tilelayer.
        * @param matrix Desired value.
        * @spicapi
        */
        void SetMatrix(const Matrix& matrix);

        /**
         * @brief Returns matrix of Tilelayer.
         * @return Matrix.
         * @spicapi
         */
        Matrix GetMatrix() const;

        /**
         * @brief Returns tile size of tile in tile layer.
         * @return int.
         * @spicapi
         */
        int GetTilesize() const;

        /**
         * @brief Returns size of tile layer.
         * @return spic::Point.
         * @spicapi
         */
        Point GetSize() const;
    private:
        /**
         * @brief Returns sprite with tile data.
         * @return spic::Sprite.
         * @spicapi
         */
        std::unique_ptr<Sprite> GetSprite(const TileSet& tileSet, const int x, const int y, const int tileSize);
    private:
        int tileSize;
        int layerIndex;
        Matrix tileMatrix;
        std::vector<TileSet> tilesets;
    };
}

#endif // TILELAYER_H_