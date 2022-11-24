#pragma once

#include <string>
#include <vector>
#include <tinyxml.h>
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
        TileLayer(const int tilesize, const std::vector<TileSet> tilesets);

        virtual ~TileLayer();

        inline void Render();

        void SetMatrix(const Matrix& matrix);

        inline Matrix GetMatrix() const;

        inline int GetTilesize() const;

        inline Point GetSize() const;
    private:
        int tileSize;
        Matrix tileMatrix;
        std::vector<TileSet> tilesets;
    };
}