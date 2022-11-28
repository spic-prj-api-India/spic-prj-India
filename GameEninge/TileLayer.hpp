#ifndef TILELAYER_H_
#define TILELAYER_H_

#include <vector>
#include <iostream>
#include "TileSet.hpp"
#include "Point.hpp"
#include "GameObject.hpp"

namespace spic::internal
{
    using Matrix = std::vector<std::vector<int>>;

    class TileLayer
    {
    public:
        TileLayer(const int layerIndex, const int tilesize, const std::vector<TileSet> tilesets);

        virtual ~TileLayer();

        void Render();

        void SetMatrix(const Matrix& matrix);

        void CreateEntities() const;

        inline Matrix GetMatrix() const;

        inline int GetTilesize() const;

        inline Point GetSize() const;
    private:
        std::unique_ptr<Sprite> GetSprite(const TileSet& tileSet, const int x, const int y, const int tileSize);
        void CreateEntity(const float x, const float y, const std::string& name) const;
    private:
        int tileSize;
        int layerIndex;
        Matrix tileMatrix;
        std::vector<TileSet> tilesets;
    };
}

#endif // TILELAYER_H_