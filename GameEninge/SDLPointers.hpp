#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <memory>

#define UINT_8_BEGIN 0
#define UINT_8_END 255

namespace spic::internal::rendering::impl
{
	/**
	 * @brief Custom deleter for sdl
	*/
	struct SDL_Deleter {
		void operator()(SDL_Surface* ptr) { if (ptr) SDL_FreeSurface(ptr); }
		void operator()(SDL_Texture* ptr) { if (ptr) SDL_DestroyTexture(ptr); }
		void operator()(SDL_Renderer* ptr) { if (ptr) SDL_DestroyRenderer(ptr); }
		void operator()(SDL_Window* ptr) { if (ptr) SDL_DestroyWindow(ptr); }
		void operator()(SDL_RWops* ptr) { if (ptr) SDL_RWclose(ptr); }
		void operator()(TTF_Font* ptr) { if (ptr) TTF_CloseFont(ptr); }
	};

	/**
	 * @brief unique_ptr for SDL stuff
	*/
	using SurfacePtr = std::unique_ptr<SDL_Surface, SDL_Deleter>;
	using TexturePtr = std::unique_ptr<SDL_Texture, SDL_Deleter>;
	using RendererPtr = std::shared_ptr<SDL_Renderer>;
	using RendererPtrWeak = std::weak_ptr<SDL_Renderer>;
	using WindowPtr = std::unique_ptr<SDL_Window, SDL_Deleter>;
	using RWopsPtr = std::unique_ptr<SDL_RWops, SDL_Deleter>;
	using FontPtr = std::unique_ptr<TTF_Font, SDL_Deleter>;

}