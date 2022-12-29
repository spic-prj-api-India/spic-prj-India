#include "RenderTextures.hpp"
#include "Defaults.hpp"
#include "GeneralHelper.hpp"
#include "Settings.hpp"
#include "Debug.hpp"

spic::internal::rendering::impl::RenderTextures::RenderTextures(RendererPtrWeak renderer)
{
	auto tmp_sprites = SurfacePtr(IMG_Load(spic::internal::defaults::MISSING_TEXTURE.c_str()));
	if (!tmp_sprites.get())
	{
		spic::debug::LogError("Failed to create RenderTextures class");
		exit(-1);
	}

	missingTexture = TexturePtr(SDL_CreateTextureFromSurface(renderer.lock().get(), tmp_sprites.get()));

	this->renderer = renderer;
}

SDL_Texture* spic::internal::rendering::impl::RenderTextures::LoadTexture(const std::string& sprite)
{
	if (sprite.empty())
		return missingTexture.get();
	bool exists = textures.find(sprite) != textures.end();

	if (exists)
		return textures[sprite].get();

	auto tmp_sprites = SurfacePtr(IMG_Load(sprite.c_str()));
	if (!tmp_sprites.get())
		return missingTexture.get();

	auto a = this->renderer.lock().get();

	auto texture = TexturePtr(SDL_CreateTextureFromSurface(a, tmp_sprites.get()));
	auto returnPtr = texture.get();
	textures.emplace(sprite, std::move(texture));
	return returnPtr;
}

spic::Point spic::internal::rendering::impl::RenderTextures::GetTextureSize(SDL_Texture* texture) const
{
	int x = -1;
	int y = -1;
	SDL_QueryTexture(texture, NULL, NULL, &x, &y);
	return spic::Point{static_cast<float>(x), static_cast<float>(y)};
}

void spic::internal::rendering::impl::RenderTextures::Reset()
{
	this->textures.clear();
}

void spic::internal::rendering::impl::RenderTextures::SetTextureColor(SDL_Texture* texture, const spic::Color& color)
{
	auto _color = RenderTextures::ConvertsColor(color);

	SDL_SetTextureColorMod(texture
		, _color.r
		, _color.g
		, _color.b);

	SDL_SetTextureAlphaMod(texture,
		_color.a);
}

void spic::internal::rendering::impl::RenderTextures::RenderTexture(SDL_Texture* texture, const SDL_Rect* source, const SDL_FRect* destination, const double rotationDegrees, SDL_RendererFlip flip)
{
	if (auto render = this->renderer.lock(); render != nullptr)
	{
		SDL_RenderCopyExF(render.get(), texture, source, destination, rotationDegrees, NULL, flip);
	}
}

SDL_RendererFlip spic::internal::rendering::impl::RenderTextures::GetFlip(const bool flipX, const bool flipY)
{
	if (flipX && flipY)
		return (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	else if (flipX)
		return SDL_FLIP_HORIZONTAL;
	else if (flipY)
		return SDL_FLIP_VERTICAL;

	return SDL_FLIP_NONE;
}

SDL_Color spic::internal::rendering::impl::RenderTextures::ConvertsColor(const spic::Color& color)
{
	using namespace spic::helper_functions::general_helper;

	return SDL_Color{ static_cast<unsigned char>(PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.R())))
	, static_cast<unsigned char>(PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.G())))
	, static_cast<unsigned char>(PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.B()))) 
	, static_cast<unsigned char>(PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.A())))};
}