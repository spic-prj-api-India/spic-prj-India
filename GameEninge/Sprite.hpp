#ifndef SPRITERENDERER_H_
#define SPRITERENDERER_H_

#include "Component.hpp"
#include "Color.hpp"
#include <string>

namespace spic {

    /**
     * @brief A component representing a sprite (small image)
     * @spicapi
     */
    class Sprite : public Component {

    public:
        
        Sprite();
        Sprite(const std::string& sprite
            , const bool flipX
            , const bool flipY
            , const int sortingLayer
            , const int orderInLayer
            , const int x = 0
            , const int y = 0
            , const int height = 0
            , const int width = 0);

        Sprite(const spic::Color& color
            , const bool flipX
            , const bool flipY
            , const int sortingLayer
            , const int orderInLayer
            , const int x = 0
            , const int y = 0
            , const int height = 0
            , const int width = 0);

        const std::string _Sprite() const;
        const void _Sprite(const std::string& sprite);

        const spic::Color Color() const;
        const void Color(const spic::Color& color);

        const bool FlipX() const;
        const void FlipX(const bool flipx);

        const bool FlipY() const;
        const void FlipY(const bool flipy);

        const int SortingLayer() const;
        const void SortingLayer(const int sortingLayer);

        const int OrderInLayer() const;
        const void OrderInLayer(const int orderInLayer);

        const int X() const;
        const void X(int newX);

        const int Y() const;
        const void Y(int newY);

        const int Height() const;
        const void Height(int newHeight);

        const int Width() const;
        const void Width(int newWidth);

        virtual bool operator <(Sprite const& a);

    private:
        std::string sprite;
        spic::Color color;
        bool flipX;
        bool flipY;
        int sortingLayer;
        int orderInLayer;
        int x;
        int y;
        int height;
        int width;
    };

}

#endif // SPRITERENDERER_H_
