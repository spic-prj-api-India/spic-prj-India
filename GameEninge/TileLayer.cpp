#include "TileLayer.hpp"

namespace spic::internal
{
    TileLayer::TileLayer(const int tilesize, const std::vector<TileSet> tilesets) : tileSize(tilesize), tilesets(tilesets) 
    {}

    TileLayer::~TileLayer()
    {
        tileMatrix.clear();
        tileMatrix.shrink_to_fit();
        tilesets.clear();
        tilesets.shrink_to_fit();
    }

    inline void TileLayer::Render()
    {
        for (unsigned int i = 0; i < tileMatrix.size(); i++)
        {
            for (unsigned int j = 0; j < tileMatrix[1].size(); j++)
            {
                int tileId = tileMatrix[i][j];
                if (tileId == 0) continue;

                else {
                    tileId--;
                    int tilesetIndex = 0;

                    if (tilesets.size() > 1) {
                        for (unsigned int k = 1; k < tilesets.size(); k++)
                        {
                            if (tileId >= (tilesets[k].firstId - 1) && tileId < tilesets[k].lastId)
                            {
                                tileId = tileId + tilesets[k].tileCount - tilesets[k].lastId;
                                tilesetIndex = k;
                                break;
                            }
                        }
                    }

                    const int tileRow = static_cast<int>(tileId / tilesets[tilesetIndex].columnCount);
                    const int tileCol = static_cast<int>(tileId - (tilesets[tilesetIndex].columnCount * tileRow));

                   /* const Transform transform = Transform(tilesets[tilesetIndex].textureId, PointFloat(j * tileSize, i * tileSize));
                    const SDL_Rect srcRect = { tileCol * tileSize, tileRow * tileSize, tileSize, tileSize };
                    Renderer::Get()->DrawSprite(transform, srcRect);*/
                }
            }
        }
    }

    void TileLayer::SetMatrix(const Matrix& matrix)
    {
        tileMatrix = matrix;
    }

    inline Matrix TileLayer::GetMatrix() const
    {
        return tileMatrix;
    }

    inline int TileLayer::GetTilesize() const
    {
        return tileSize;
    }

    inline Point TileLayer::GetSize() const
    {
        return Point(tileMatrix.size(), tileMatrix[1].size());
    }
}