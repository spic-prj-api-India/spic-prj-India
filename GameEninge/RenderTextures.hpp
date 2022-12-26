#ifndef RENDERERTEXTURES_H_
#define RENDERERTEXTURES_H_

#include <map>
#include <string>
#include "SDLPointers.hpp"
#include "Point.hpp"
#include "GeneralHelper.hpp"

namespace spic::internal::rendering::impl
{
	/**
	 * @brief The renderer class that is in charge of rendering textures
	*/
	class RenderTextures
	{
	private:
		/**
		 * @brief Texture map
		*/
		std::map<std::string, TexturePtr> textures;

		/**
		 * @brief Missing texture
		*/
		TexturePtr missingTexture;

		/**
		 * @brief The curent renderer object
		*/
		RendererPtrWeak renderer;

	public:

		/**
		 * @brief Constructor
		 * @param renderer An reference to the current renderer
		*/
		RenderTextures(RendererPtrWeak renderer);

		/**
		 * @brief Loads textures into the textures map
		 * @param sprite The sprite to load
		 * @return An texture ptr
		*/
		SDL_Texture* LoadTexture(const std::string& sprite);

		/**
		 * @brief Gets size of texture
		 * @param texture
		 * @return An point object where x is the width en y is the height
		*/
		Point GetTextureSize(SDL_Texture* texture) const;
		
		/**
		 * @brief Resets the textures map
		*/
		void Reset();

		/**
		 * @brief Sets texture color modulation and and alpha modulation
		 * @param texture The texture
		 * @param color The color
		*/
		void SetTextureColor(SDL_Texture* texture, const spic::Color& color);

		/**
		 * @brief Renders an texture
		 * @param texture The texture to render
		 * @param source The source rectangle
		 * @param destination The destination rectangle
		 * @param rotationDegrees The rotation where origin is center
		 * @param flip If the sprite should be flipped (horizontal and vertical)
		*/
		void RenderTexture(SDL_Texture* texture, const SDL_Rect* source, const SDL_FRect* destination, const double rotationDegrees, SDL_RendererFlip flip);

		/**
		 * @brief Gets the render bit flip
		 * @param flipX IF the x acces needs to be flipped
		 * @param flipY If the y acces needs to be flipped
		 * @return The current renderFlip
		*/
		static SDL_RendererFlip GetFlip(const bool flipX, const bool flipY);

		/**
		 * @brief Converts the spic::Color to SDL_Color
		 * @param color
		 * @return SDL_Color
		*/
		static SDL_Color ConvertsColor(const spic::Color& color);
	};
}
#endif //RENDERERTEXTURES_H_