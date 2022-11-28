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
        /// @brief default constructor
        /// @details the default color is white color swapping of textures
        Sprite();

        /// @brief 
        /// @param sprite 
        /// @param color 
        /// @param flipX 
        /// @param flipY 
        /// @param sortingLayer 
        /// @param orderInLayer 
        /// @param x 
        /// @param y 
        /// @param height 
        /// @param width 
        Sprite(const std::string& sprite
            , const int sortingLayer = 0
            , const int orderInLayer = 0
            , const spic::Color& color = Color::white()
            , const bool flipX = false
            , const bool flipY = false
            , const int x = 0
            , const int y = 0
            , const int height = 0
            , const int width = 0);

        const std::string _Sprite() const;
        void _Sprite(const std::string& sprite);

        const spic::Color Color() const;
        void Color(const spic::Color& color);

        const bool FlipX() const;
        void FlipX(const bool flipx);

        const bool FlipY() const;
        void FlipY(const bool flipy);

        const int SortingLayer() const;
        void SortingLayer(const int sortingLayer);

        const int OrderInLayer() const;
        void OrderInLayer(const int orderInLayer);

        const int X() const;
        const void X(int newX);

        const int Y() const;
        const void Y(int newY);

        const int Height() const;
        const void Height(int newHeight);

        const int Width() const;
        const void Width(int newWidth);

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
