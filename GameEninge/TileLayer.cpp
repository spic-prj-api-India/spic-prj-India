#include "TileLayer.hpp"
#include "Renderer.hpp"

namespace spic::internal
{
    TileLayer::TileLayer(const  int layerIndex, const int tilesize, const std::vector<TileSet> tilesets) :
        layerIndex{ layerIndex }, tileSize(tilesize), tilesets(tilesets)
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

                    std::unique_ptr<Sprite> sprite = GetSprite(tilesets[tilesetIndex], tileCol * tileSize, tileRow * tileSize, tileSize);
                    float x = static_cast<float>(j * tileSize);
                    float y = static_cast<float>(i * tileSize);
                    std::unique_ptr<Transform> transform = std::make_unique<Transform>(Point(x, y), 0.0f, 1.0f);
                    Rendering::DrawSprite(transform.release(), sprite.release());
                }
            }
        }
    }

    std::unique_ptr<Sprite> TileLayer::GetSprite(const TileSet& tileSet, const int x, const int y, const int tileSize)
    {
        std::unique_ptr<Sprite> sprite = std::make_unique<Sprite>();
        sprite->_Sprite(tileSet.source);
        sprite->SortingLayer(layerIndex);
        sprite->X(x);
        sprite->Y(y);
        sprite->Height(tileSize);
        sprite->Width(tileSize);
        return std::move(sprite);
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
        float sizeX = static_cast<float>(tileMatrix.size());
        float sizeY = static_cast<float>(tileMatrix[1].size());
        return Point(sizeX, sizeY);
    }
}