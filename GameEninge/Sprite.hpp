#ifndef SPRITERENDERER_H_
#define SPRITERENDERER_H_

#include "Component.hpp"
#include "Color.hpp"
#include <string>

namespace spic {
    /**
     * @brief A component representing a sprite (small image).
	 *		Color in this case represents color modulation. 
			This means that if it's white there is no color modulation
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
		 * @brief Gets color modulation of Sprite.
		 * @return spic::Color.
		 */
		const spic::Color Color() const;

		/**
		 * @brief Sets color modulation of Sprite.
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

		/**
		 * @brief Gets height of Sprite in texture.
		 * @return int.
		 * @sharedapi
		 */
		const float DisplayHeight() const;

		/**
		* @brief Sets height of Sprite in texture. 
		* @param newHeight Desired value.
		* @sharedapi
		*/
		const void DisplayHeight(float newHeight); 


		/*@brief Gets width of Sprite in texture.
		* @return int.
		* @sharedapi
		*/
		const float DisplayWidth() const; 

		/**
		* @brief Sets width of Sprite in texture.
		* @param newWidth Desired value.
		* @sharedapi
		*/
		const void DisplayWidth(float newWidth); 
	private:

		/**
		 * @brief The location where the sprite is
		*/
		std::string sprite;

		/**
		 * @brief Color modulation. White means no modulation
		*/
		spic::Color color;

		/**
		 * @brief If the texture is flipped in the x direction
		*/
		bool flipX;

		/**
		 * @brief If the texture is flipped in the y direction
		*/
		bool flipY;

		/**
		 * @brief Which position it gets after it gets sorted into orders
		*/
		int sortingLayer;

		/**
		 * @brief Which postion it gets
		*/
		int orderInLayer;

		/**
		 * @brief X pos in sprite sheet
		*/
		int x;

		/**
		 * @brief Y pos in sprite sheet
		*/
		int y;

		/**
		 * @brief Height of sprite in sprite sheet
		*/
		int height;

		/**
		 * @brief Width of sprite in sprite sheet
		*/
		int width;

		/**
		 * @brief Display height on window. If not set, height of texture is used for rendering sprite.
		*/
		float displayHeight;

		/**
		 * @brief Display width on window. If not set, width of texture is used for rendering sprite.
		*/
		float displayWidth;
	};

}

#endif // SPRITERENDERER_H_
