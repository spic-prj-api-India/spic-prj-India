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

        void Render();

        void SetMatrix(const Matrix& matrix);

        Matrix GetMatrix() const;

        int GetTilesize() const;

        Point GetSize() const;
    private:
        std::unique_ptr<Sprite> GetSprite(const TileSet& tileSet, const int x, const int y, const int tileSize);
    private:
        int tileSize;
        int layerIndex;
        Matrix tileMatrix;
        std::vector<TileSet> tilesets;
    };
}

#endif // TILELAYER_H_