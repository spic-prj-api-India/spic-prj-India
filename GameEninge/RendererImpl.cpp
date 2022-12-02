#include "RendererImpl.hpp"
#include "UIObject.hpp"
#include <algorithm>
#include "Text.hpp"
#include "Animator.hpp"
#include "GeneralHelper.hpp"
#include <sstream>
#include <string_view>
#include <stdio.h>
#include <filesystem>
#include "TypeHelper.hpp"
#include "StringHelper.hpp"

using namespace spic;
using namespace spic::window;
using namespace spic::internal::rendering;
using namespace spic::GeneralHelper;
#define UINT_8_BEGIN 0
#define UINT_8_END 255

RendererImpl* RendererImpl::pinstance_{ nullptr };
std::mutex RendererImpl::mutex_;

RendererImpl::RendererImpl() noexcept(false) : camera{ 0, 0, 0, 0 }, backgroundColor{ 0,0,0,1 }, backgroundImage{""}, scaling{1}, rotation{0}
{
}

RendererImpl::~RendererImpl()
{
	try
	{
		Exit();
	}
	catch (...)
	{

	}
}

RendererImpl* RendererImpl::GetInstance()
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (pinstance_ == nullptr)
	{
		pinstance_ = new RendererImpl();
	}
	return pinstance_;
}

void RendererImpl::Start(const spic::window::WindowValues* values)
{
	//Exit(); // does nothing if it has not been called yet

	// sets up video
	if (SDL_Init(SDL_INIT_VIDEO != 0))
	{
		std::cout << SDL_GetError() << std::endl;
		exit(-1);
	}

	// for deltatime 
	lastTick = SDL_GetTicks();
	deltatime = 0;

	// TODO: Zet in CreateWindow
	const SDL_WindowFlags w_flags = SDL_WindowFlags(SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
	window = WindowPtr(SDL_CreateWindow(values->WindowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, values->ScreenWidth, values->ScreenHeight, w_flags));
	if (window.get() == nullptr) {
		std::cerr << SDL_GetError() << std::endl;
		exit(-1);
	}

	SDL_SetWindowAlwaysOnTop(window.get(),
		(SDL_bool)values->SetOnTop);

	// TODO: Zet in CreateRenderer
	SDL_RendererFlags rendererFlags = (SDL_RendererFlags)(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	renderer = RendererPtr(SDL_CreateRenderer(window.get(), -1, rendererFlags));
	if (renderer.get() == nullptr) {
		std::cerr << SDL_GetError() << std::endl;
		exit(-1);
	}

	//TODO: Zet in CreateTTF
	if (TTF_Init() == -1) {
		printf("Failed to TTF: %s", SDL_GetError());
		exit(-1);
	}

	this->UpdateWindow(values);


	auto tmp_sprites = SurfacePtr(IMG_Load("assets/textures/missing_texture.png"));
	if (!tmp_sprites.get())
		return;

	missingTexture = TexturePtr(SDL_CreateTextureFromSurface(renderer.get(), tmp_sprites.get()));
}

void RendererImpl::Exit()
{
	renderer.release();
	window.release();
	SDL_Quit();
}

void RendererImpl::DrawGameObject(GameObject* gameObject, bool isUiOject)
{
	if (gameObject->Active())
	{
		auto* castedUiObject = dynamic_cast<UIObject*>(gameObject);
		const bool thisIsUIObject = castedUiObject != nullptr;


		if (!isUiOject && thisIsUIObject)
		{
			isUiOject = thisIsUIObject;
		}

		DrawSprites(gameObject, isUiOject);

		DrawAnimators(gameObject, isUiOject);

		for (auto& child : gameObject->GetChildren())
		{
			DrawGameObject(child.get(), isUiOject);
		}

		if (isUiOject)
			DrawUI(castedUiObject);
	}
}

void RendererImpl::DrawSprites(GameObject* gameObject, const bool isUIObject)
{
	const auto transform = gameObject->Transform();
	auto _sprites = gameObject->GetComponents<Sprite>();
	std::sort(_sprites.begin(), _sprites.end(), spic::GeneralHelper::SpriteSorting);
	for (auto& sprite : _sprites)
	{
		if (isUIObject)
			DrawUISprite(TypeHelper::CastPtrToType<UIObject>(gameObject), sprite.get(), transform.get());
		else
			DrawSprite(sprite.get(), transform.get());
	}
}

void RendererImpl::DrawAnimators(GameObject* gameObject, const bool isUiObject)
{
	auto _animator = gameObject->GetComponents<Animator>();

	for (auto& animator : _animator)
	{
		DrawAnimator(gameObject, animator.get(), gameObject->Transform().get(), isUiObject);
	}
}

void RendererImpl::DrawAnimator(GameObject* gameObject, Animator* animator, const Transform* transform, const bool isUIObject)
{
	auto sprites = animator->Sprites();
	// sort sprites

	const auto framesAmount = sprites.back()->OrderInLayer();

	const int fps = 1000;

	//const auto frame = static_cast<uint64_t>(SDL_GetTicks() / ((static_cast<double>(fps) / animator->Fps()) * Time::TimeScale())) % framesAmount;

	const auto frame = static_cast<uint64_t>(SDL_GetTicks() / (1000 / animator->Fps() * Time::TimeScale())) % framesAmount;

	for (auto& sprite : sprites)
	{
		if (sprite->OrderInLayer() == frame && !animator->IsFrozen())
		{
			//animator->Index(frame);
			if (isUIObject)
				DrawUISprite(TypeHelper::CastPtrToType<UIObject>(gameObject), sprite.get(), transform);
			else
				DrawSprite(sprite.get(), transform);
		}
		else if (sprite->OrderInLayer() == animator->Index() && animator->IsFrozen()) {
			if (isUIObject)
				DrawUISprite(TypeHelper::CastPtrToType<UIObject>(gameObject), sprite.get(), transform);
			else
				DrawSprite(sprite.get(), transform);
		}
	}
}

void RendererImpl::DrawUISprite(UIObject* uiObject, const Sprite* sprite, const Transform* transform)
{
	if (transform == nullptr)
		return;

	SDL_Texture* texture = LoadTexture(sprite->_Sprite());
	auto textureSize = GetTextureSize(texture);

	SDL_FRect dstRect = { transform->position.x
		, transform->position.y
		, uiObject->Width() * transform->scale
		, uiObject->Height() * transform->scale };

	if (!SDL_HasIntersectionF(&dstRect, &this->windowCamera))
		return;

	DrawSprite(sprite, transform, texture, &dstRect, NULL);
}

void RendererImpl::DrawSprite(const Sprite* sprite, const Transform* transform)
{
	if (transform == nullptr)
		return;

	SDL_Texture* texture = LoadTexture(sprite->_Sprite());
	auto textureSize = GetTextureSize(texture);

	const int width = (sprite->Width() == 0) ? textureSize.x : sprite->Width();
	const int height = (sprite->Height() == 0) ? textureSize.y : sprite->Height();
	SDL_FRect dstRect = { transform->position.x
		, transform->position.y
		, width * transform->scale * this->scaling
		, height * transform->scale * this->scaling };

	SDL_Rect sourceRect = { PrecisionRoundingoInt(sprite->X())
		, PrecisionRoundingoInt(sprite->Y())
		, PrecisionRoundingoInt(width)
		, PrecisionRoundingoInt(height) };

	if (SDL_HasIntersectionF(&dstRect, &this->camera))
	{
		dstRect = { dstRect.x - this->camera.x
			, dstRect.y - this->camera.y
			, dstRect.w
			, dstRect.h };
	}
	else
		return;

	DrawSprite(sprite, transform, texture, &dstRect, &sourceRect);
}

void RendererImpl::DrawSprite(const Sprite* sprite, const Transform* transform, SDL_Texture* texture, SDL_FRect* dstRect, SDL_Rect* sourceRect) {
	const auto color = sprite->Color();

	SDL_SetTextureColorMod(texture
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.R()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.G()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.B())));

	SDL_SetTextureAlphaMod(texture,
		PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.A())));

	auto center = SDL_FPoint{ dstRect->x + (dstRect->w / 2)
		,dstRect->y + (dstRect->h / 2) };

	SDL_RendererFlip flip = GetFlip(sprite->FlipX(), sprite->FlipY());

	double angle = RAD2DEG<double>(transform->rotation);
	if (texture == nullptr) {
		SDL_RenderCopyExF(renderer.get(), NULL, sourceRect, dstRect, angle, NULL, flip);
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	SDL_RenderCopyExF(renderer.get(), texture, sourceRect, dstRect, angle, NULL, flip);
}

SDL_Texture* RendererImpl::LoadTexture(const std::string& sprite)
{
	if (sprite.empty())
		return missingTexture.get();
	bool exists = textures.find(sprite) != textures.end();
	if (exists)
		return textures[sprite].get();

	auto tmp_sprites = SurfacePtr(IMG_Load(sprite.c_str()));
	if (!tmp_sprites.get())
		return missingTexture.get();

	auto texture = TexturePtr(SDL_CreateTextureFromSurface(renderer.get(), tmp_sprites.get()));
	auto returnPntr = texture.get();
	textures.emplace(sprite, std::move(texture));
	return returnPntr;
}

SDL_Point RendererImpl::GetTextureSize(SDL_Texture* texture) const
{
	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
	return size;
}

SDL_RendererFlip RendererImpl::GetFlip(const bool flipX, const bool flipY)
{
	if (flipX && flipY)
		return (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	else if (flipX)
		return SDL_FLIP_HORIZONTAL;
	else if (flipY)
		return SDL_FLIP_VERTICAL;
	return SDL_FLIP_NONE;
}

void RendererImpl::DrawUI(UIObject* gameObject)
{
	auto* castedUiObject = dynamic_cast<Text*>(gameObject);
	const bool thisIsTextObject = castedUiObject != nullptr;
	if (thisIsTextObject)
		DrawText(castedUiObject);
}

void RendererImpl::DrawText(Text* text)
{
	if (std::filesystem::exists(text->Font().c_str()))
	{
		auto font = TTF_OpenFont(text->Font().c_str(), text->Size());
		auto transform = text->Transform().get();
		auto colour = SDL_Color{ static_cast<unsigned char>(PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, text->Color().R())))
			, static_cast<unsigned char>(PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, text->Color().G())))
			, static_cast<unsigned char>(PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, text->Color().B()))) };
		std::string texts{ text->_Text() };
		text->Alignment();

		const spic::GameObject* parent = text->GetParent();
		const float x = transform->position.x + (parent != nullptr ? parent->Transform()->position.x : 0);
		const float y = transform->position.y + (parent != nullptr ? parent->Transform()->position.y : 0);
		this->RenderMultiLineText(font, texts, colour, x, y, text->Width(), text->Height(), 2, text->Alignment());

		TTF_CloseFont(font);
	}
}

void RendererImpl::Wrap(const TTF_Font* pFont, std::string& input, const float width)
{
	std::istringstream in(input);
	std::string line;
	size_t current = 0;
	std::string word;
	std::string output = "";

	int* w = new int{ 0 };
	int* h = new int{ 0 };

	try
	{
		while (std::getline(in, line))
		{
			std::istringstream linein(line);
			while (linein >> word) {
				*w = 0;
				*h = 0;
				TTF_SizeUTF8((TTF_Font*)pFont, word.c_str(), w, h);
				if (current + *w + 1 > width)
				{
					output += "\n";
				}
				output += word + ' ';
				current += *w + 1;
			}
			output += "\n";
			current = 0;
		}
	}
	catch (...)
	{

	}

	delete w;
	delete h;
	std::swap(output, input);
}

void RendererImpl::RenderMultiLineText(const TTF_Font* pFont, std::string& rText
	, const SDL_Color& rTextColor, float xPosition, float yPosition, const float width
	, const float height, const int distanceBetweenLines, const Alignment align)
{
	// Make sure that the string contains at least 1 character
	if (rText.empty())
		return;
	Wrap(pFont, rText, width);
	try
	{
		SurfacePtr pSurface;
		TexturePtr pTexture;

		int currentLine = 0;
		float totalLength = 0;

		// This string will contain one line of text
		std::string textLine = "";

		for (int i = 0; i < rText.length(); ++i)
		{
			// Create the text line as long as the current character is not a \n command
			if (rText.at(i) != '\n') {
				textLine += rText.at(i);
				continue;
			}

			// Since the current character is now a \n command, it's time to create the texture containing the current text line,
			// render it, clear the created text string and then start on a new line
			if (pFont)
				pSurface.reset(TTF_RenderText_Solid((TTF_Font*)pFont, textLine.c_str(), rTextColor));

			// The current line of text has now been rendered (if the texture was successfully created and so on) and the text line string now needs to be cleared
			textLine = "";

			// Time for a new line
			++currentLine;

			if (!pSurface.get())
				continue;
			pTexture.reset(SDL_CreateTextureFromSurface(this->renderer.get(), pSurface.get()));

			if (pTexture.get())
			{
				const float textWidth = static_cast<float>(pSurface->w);
				const float textHeight = static_cast<float>(pSurface->h);
				const float nextY = yPosition + ((textHeight + distanceBetweenLines) * currentLine);

				totalLength += nextY - yPosition;

				if (totalLength > height)
				{
					pTexture.reset(NULL);
					break;
				}

				SDL_FRect PositionQuad = { 0, 0, 0, 0 };

				switch (align) {
				case Alignment::CENTER: // Position the quad centered (horizontal) in the window
					PositionQuad.x = (width / 2) - (textWidth / 2) + xPosition;
					break;
				case Alignment::RIGHT:
					PositionQuad.x = width - textWidth + xPosition;
					break;
				default: // Position the quad according to the XPosition parameter
					PositionQuad.x = xPosition;
				}

				PositionQuad.y = nextY;
				PositionQuad.w = textWidth;
				PositionQuad.h = textHeight;


				SDL_RenderCopyF(this->renderer.get(), pTexture.get(), NULL, &PositionQuad);

				// Avoid memory leak
				pTexture.reset(NULL);
			}

			// Avoid memory leak
			pSurface.reset(NULL);
		}
	}
	catch (...)
	{
		return;
	}
}

TTF_Font* RendererImpl::LoadFont(const std::string& font, const int size)
{
	if (font.empty())
		return nullptr;
	bool exists = fonts.find(font) != fonts.end();
	if (exists)
		return fonts[font].get();

	auto tmp_font = FontPtr(TTF_OpenFont(font.c_str(), size));
	if (!tmp_font.get())
		return nullptr;

	return tmp_font.get();
}

void RendererImpl::NewScene()
{
	textures.clear();
	fonts.clear();
}

void RendererImpl::SetBackgroundColor()
{
	SDL_SetRenderDrawColor(renderer.get()
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.R()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.G()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.B()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.A()))
	);

	SDL_RenderFillRectF(renderer.get(), &this->windowCamera);
}

void RendererImpl::DrawRect(const SDL_FRect* rect, const double angle, const Color* colour)
{
	std::string defaultRectanglePath = StringHelper::GetBasePath() + "\\assets\\textures\\UISprite.png";
	SDL_Texture* texture = LoadTexture(defaultRectanglePath);
	SDL_SetRenderDrawColor(renderer.get()
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, colour->R()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, colour->G()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, colour->B()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, colour->A())));
	SDL_RenderCopyExF(renderer.get(), NULL, NULL, rect, angle, NULL, SDL_FLIP_NONE);
}

void RendererImpl::DrawLine(const Point* start, const Point* end, const Color* colour)
{
	SDL_SetRenderDrawColor(renderer.get()
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, colour->R()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, colour->G()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, colour->B()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, colour->A())));
	SDL_RenderDrawLine(renderer.get()
		, PrecisionRoundingoInt(start->x)
		, PrecisionRoundingoInt(start->y)
		, PrecisionRoundingoInt(end->x)
		, PrecisionRoundingoInt(end->y));
}

void RendererImpl::UpdateCamera(Camera* camera)
{
	auto transform = camera->Transform().get();
	const auto pos = transform->position;
	this->scaling = transform->scale;
	this->rotation = transform->rotation;

	int width, height = 0;
	SDL_GetWindowSize(window.get(), &width, &height);
	this->camera =
	{ pos.x
	, pos.y
	, static_cast<float>(width)
	, static_cast<float>(height) };

	this->backgroundColor = camera->BackgroundColor();
	this->backgroundImage = camera->BackgroundImage();
}

void RendererImpl::Clean()
{
	SDL_RenderClear(renderer.get());

	if (!backgroundImage.empty()) {
		auto texture = LoadTexture(backgroundImage);
		SDL_RenderCopy(renderer.get(), texture, NULL, NULL);
	}
	SDL_SetRenderDrawColor(renderer.get()
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.R()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.G()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.B()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.A()))
	);
}

void RendererImpl::Render()
{
	SDL_SetRenderDrawColor(renderer.get()
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.R()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.G()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.B()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.A()))
	);

	SDL_RenderPresent(renderer.get());
}

void RendererImpl::UpdateWindow(const spic::window::WindowValues* values)
{
	Uint32 window_flags = -1;

	switch (values->selector)
	{
	case FULLSCREENTYPE::BORDERLESS:
		window_flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
		break;
	case FULLSCREENTYPE::FULLSCREEN:
		window_flags = SDL_WINDOW_FULLSCREEN;
		break;
	case FULLSCREENTYPE::WINDOWED:
		window_flags = 0;
		break;
	}

	if (window_flags != -1)
		SDL_SetWindowFullscreen(window.get(),
			window_flags);

	int width, height = 0;
	SDL_GetWindowSize(window.get(), &width, &height);
	this->windowCamera = { 0, 0, static_cast<float>(width), static_cast<float>(height) };
	this->camera.w = static_cast<float>(width);
	this->camera.h = static_cast<float>(height);
}