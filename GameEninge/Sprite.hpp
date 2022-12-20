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
		/// @param sortingLayer Default 0 
		/// @param orderInLayer Default 0 
		/// @param color Default white 
		/// @param flipX Default false 
		/// @param flipY Default false
		/// @param x Default 0 
		/// @param y Default 0 
		/// @param height Default 0 
		/// @param width Default 0 
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

		/**
		 * @brief Gets texture path of Sprite.
		 * @return string.
		 */
		const std::string _Sprite() const;

		/**
		 * @brief Sets texture path of Sprite.
		 * @param sprite Desired value.
		 */
		void _Sprite(const std::string& sprite);

		/**
		 * @brief Gets color of Sprite.
		 * @return spic::Color.
		 */
		const spic::Color Color() const;

		/**
		 * @brief Sets color of Sprite.
		 * @param color Desired value.
		 */
		void Color(const spic::Color& color);

		/**
		 * @brief Gets flip x of Sprite.
		 * @return bool.
		 */
		const bool FlipX() const;

		/**
		* @brief Sets flip x of Sprite.
		* @param flipX Desired value.
		*/
		void FlipX(const bool flipX);

		/**
		 * @brief Gets flip y of Sprite.
		 * @return bool.
		 * @spicapi
		 */
		const bool FlipY() const;

		/**
		* @brief Sets flip y of Sprite.
		* @param flipY Desired value.
		* @spicapi
		*/
		void FlipY(const bool flipY);

		/**
		 * @brief Gets sorting layer of Sprite.
		 * @return int.
		 * @spicapi
		 */
		const int SortingLayer() const;

		/**
		* @brief Sets sorting layer of Sprite.
		* @param sortingLayer Desired value.
		* @spicapi
		*/
		void SortingLayer(const int sortingLayer);

		/**
		 * @brief Gets order layer of Sprite.
		 * @return int.
		 * @spicapi
		 */
		const int OrderInLayer() const;

		/**
	    * @brief Sets order layer of Sprite.
	    * @param orderInLayer Desired value.
	    * @spicapi
	    */
		void OrderInLayer(const int orderInLayer);

		/**
		 * @brief Gets x of Sprite in texture.
		 * @return int.
		 * @spicapi
		 */
		const int X() const;

		/**
		* @brief Sets x position of Sprite in texture.
		* @param newX Desired value.
		* @spicapi
		*/
		const void X(int newX);

		/**
		 * @brief Gets y of Sprite in texture.
		 * @return int.
		 * @spicapi
		 */
		const int Y() const;

		/**
		* @brief Sets y position of Sprite in texture.
		* @param newY Desired value.
		* @spicapi
		*/
		const void Y(int newY);

		/**
		 * @brief Gets height of Sprite in texture.
		 * @return int.
		 * @spicapi
		 */
		const int Height() const;

		/**
		* @brief Sets height of Sprite in texture.
		* @param newHeight Desired value.
		* @spicapi
		*/
		const void Height(int newHeight);

		/**
		 * @brief Gets width of Sprite in texture.
		 * @return int.
		 * @spicapi
		 */
		const int Width() const;

		/**
		* @brief Sets width of Sprite in texture.
		* @param newWidth Desired value.
		* @spicapi
		*/
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
