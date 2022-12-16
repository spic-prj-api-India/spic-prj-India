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
#include "Defaults.hpp"
#include "WindowValues.hpp"
#include "Debug.hpp"

using namespace spic;
using namespace spic::window;
using namespace spic::internal::rendering;
using namespace spic::GeneralHelper;

#define UINT_8_BEGIN 0
#define UINT_8_END 255

RendererImpl* RendererImpl::pinstance_{ nullptr };
std::mutex RendererImpl::mutex_;

RendererImpl::RendererImpl() noexcept(false) : camera{ 0, 0, 0, 0 }, backgroundColor{ 0,0,0,1 }, backgroundImage{ "" }, scaling{ 1 }, rotation{ 0 }
{
}

RendererImpl::~RendererImpl()
{
	try
	{
		Exit();
	}
	catch (...)
	{}
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

void RendererImpl::Start()
{
	//Exit(); // does nothing if it has not been called yet

	// sets up video
	if (SDL_Init(SDL_INIT_VIDEO != 0))
	{
		spic::Debug::LogError(SDL_GetError());
		exit(-1);
	}

	// for deltatime 
	lastTick = SDL_GetTicks();
	deltatime = 0;

	// TODO: Zet in CreateWindow
	const SDL_WindowFlags w_flags = SDL_WindowFlags(SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
	window = WindowPtr(SDL_CreateWindow(spic::window::WINDOW_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, spic::window::WINDOW_WIDTH, spic::window::WINDOW_HEIGHT, w_flags));
	if (window.get() == nullptr) {
		spic::Debug::LogError(SDL_GetError());
		exit(-1);
	}

	SDL_SetWindowAlwaysOnTop(window.get(),
		(SDL_bool)spic::window::SET_ON_TOP);

	// TODO: Zet in CreateRenderer
	SDL_RendererFlags rendererFlags = (SDL_RendererFlags)(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	renderer = RendererPtr(SDL_CreateRenderer(window.get(), -1, rendererFlags));
	if (renderer.get() == nullptr) {
		spic::Debug::LogError(SDL_GetError());
		exit(-1);
	}

	//TODO: Zet in CreateTTF
	if (TTF_Init() == -1) {
		printf("Failed to TTF: %s", SDL_GetError());
		exit(-1);
	}

	this->UpdateWindow();


	auto tmp_sprites = SurfacePtr(IMG_Load(spic::internal::Defaults::MISSING_TEXTURE.c_str()));
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
	UIObject* uiObject = nullptr;
	if (isUIObject)
		uiObject = TypeHelper::CastPtrToType<UIObject>(gameObject);
	for (auto& sprite : _sprites)
	{
		if (isUIObject)
			DrawUISprite(uiObject->Width(), uiObject->Height(), sprite.get(), transform.get());
		else
			DrawSprite(sprite.get(), transform.get());
	}
}

void RendererImpl::DrawAnimators(GameObject* gameObject, const bool isUiObject)
{
	auto _animator = gameObject->GetComponents<Animator>();

	for (auto& animator : _animator)
	{
		DrawAnimator(animator.get(), gameObject->Transform().get(), isUiObject);
	}
}

void RendererImpl::DrawAnimator(Animator* animator, const Transform* transform, const bool isUIObject)
{
	if (!animator->IsRunning())
		return;

	auto sprites = animator->Sprites();

	const auto framesAmount = sprites.back()->OrderInLayer();

	const int fps = 1000;

	//const auto frame = static_cast<uint64_t>(SDL_GetTicks() / ((static_cast<double>(fps) / animator->Fps()) * Time::TimeScale())) % framesAmount;

	const auto frame = static_cast<uint64_t>(SDL_GetTicks() / (1000 / animator->Fps() * Time::TimeScale())) % framesAmount + 1;


	for (auto& sprite : sprites)
	{
		if (sprite->OrderInLayer() == frame && !animator->IsFrozen())
		{
			DrawSprite(sprite.get(), transform, isUIObject);
		}
		else if (sprite->OrderInLayer() == animator->Index() && animator->IsFrozen()) {
			DrawSprite(sprite.get(), transform, isUIObject);
		}
	}
}

void RendererImpl::DrawUISprite(const float width, const float height, const Sprite* sprite, const Transform* transform)
{
	if (transform == nullptr)
		return;

	SDL_Texture* texture = LoadTexture(sprite->_Sprite());
	auto textureSize = GetTextureSize(texture);

	SDL_FRect dstRect = { transform->position.x
		, transform->position.y
		, width * transform->scale
		, height * transform->scale };

	if (!SDL_HasIntersectionF(&dstRect, &this->windowCamera))
		return;

	DrawSprite(sprite, transform, texture, &dstRect, NULL);
}

void RendererImpl::DrawSprite(const Sprite* sprite, const Transform* transform, bool isUiOject)
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

	if (!isUiOject)
	{
		if (SDL_HasIntersectionF(&dstRect, &this->camera))
			dstRect = { dstRect.x - this->camera.x
				, dstRect.y - this->camera.y
				, dstRect.w
				, dstRect.h };
		else
			return;
	}
	else if (isUiOject)
	{
		if (!SDL_HasIntersectionF(&dstRect, &this->windowCamera))
			return;
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

	SDL_RendererFlip flip = GetFlip(sprite->FlipX(), sprite->FlipY());

	double angle = RAD2DEG<double>(transform->rotation);
	if (texture == nullptr) {
		SDL_RenderCopyExF(renderer.get(), NULL, sourceRect, dstRect, angle, NULL, flip);
		spic::Debug::LogError(SDL_GetError());
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
	const std::string  font = text->Font();
	const char* filePath = font.c_str();
	if (std::filesystem::exists(filePath))
	{
		auto font = TTF_OpenFont(filePath, text->Size());
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
	catch (const std::exception& ex)
	{
		const std::string& message = ex.what();
		spic::Debug::LogError("Wrap text failed: " + message);
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

				totalLength = ((textHeight + distanceBetweenLines) * currentLine);

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
	catch (const std::exception& ex)
	{
		const std::string& message = ex.what();
		spic::Debug::LogError("Multiline render failed: " + message);
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

void RendererImpl::DrawRect(const spic::Rect& rect, const double angle, const spic::Color& color)
{
	SDL_FRect dstRect = SDL_FRect(rect.x, rect.y, rect.w, rect.h);
	if (!SDL_HasIntersectionF(&dstRect, &this->camera))
		return;
	dstRect.x = dstRect.x - this->camera.x;
	dstRect.y = dstRect.y - this->camera.y;

	SDL_Texture* texture = LoadTexture(spic::internal::Defaults::RECT_TEXTURE);

	SDL_SetTextureColorMod(texture
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.R()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.G()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.B())));

	SDL_SetTextureAlphaMod(texture,
		PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.A())));

	const double angleInDeg = spic::GeneralHelper::RAD2DEG<double>(angle);
	SDL_RenderCopyExF(renderer.get(), texture, NULL, &dstRect, angleInDeg, NULL, SDL_FLIP_NONE);
}

void RendererImpl::DrawCircle(const spic::Point& center, const float radius, const float pixelGap, const spic::Color& color)
{
	const float diameter = radius * 2.0f;
	SDL_FRect dstCenter = SDL_FRect(center.x - radius, center.y - radius, diameter, diameter);
	if (!SDL_HasIntersectionF(&dstCenter, &this->camera))
		return;
	dstCenter.x = dstCenter.x + radius - this->camera.x;
	dstCenter.y = dstCenter.y + radius - this->camera.y;

	SDL_SetRenderDrawColor(renderer.get()
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.R()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.G()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.B()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.A())));

	// Pixel gap configures how precise the circle is drawn
	float x = radius - pixelGap;
	float y = 0.0f;
	float dx = pixelGap;
	float dy = pixelGap;
	// if decision is above zero: y++, otherwise x++
	float decisionOver2 = dx - diameter;

	while (x >= y)
	{
		DrawPoint(dstCenter.x + x, dstCenter.y + y);
		DrawPoint(dstCenter.x + y, dstCenter.y + x);
		DrawPoint(dstCenter.x - y, dstCenter.y + x);
		DrawPoint(dstCenter.x - x, dstCenter.y + y);
		DrawPoint(dstCenter.x - x, dstCenter.y - y);
		DrawPoint(dstCenter.x - y, dstCenter.y - x);
		DrawPoint(dstCenter.x + y, dstCenter.y - x);
		DrawPoint(dstCenter.x + x, dstCenter.y - y);

		if (decisionOver2 <= 0.0f)
		{
			y += pixelGap;
			decisionOver2 += dy;
			dy += 2 * pixelGap;
		}
		if (decisionOver2 > 0.0f)
		{
			x -= pixelGap;
			dx += 2 * pixelGap;
			decisionOver2 += (-diameter) + dx;
		}
	}
}

void RendererImpl::DrawPoint(const spic::Point& point, const spic::Color& color)
{
	SDL_FPoint dstPoint = { point.x , point.y };
	if (!SDL_PointInFRect(&dstPoint, &this->camera)) {
		return;
	}
	dstPoint.x = dstPoint.x - this->camera.x;
	dstPoint.y = dstPoint.y - this->camera.y;

	SDL_SetRenderDrawColor(renderer.get()
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.R()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.G()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.B()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.A())));

	DrawPoint(dstPoint.x, dstPoint.y);
}

void RendererImpl::DrawPoint(const float x, const float y) {
	SDL_RenderDrawPointF(renderer.get(), x, y);
}

void RendererImpl::DrawLine(const spic::Point& start, const spic::Point& end, const spic::Color& color)
{
	SDL_FPoint startPoint = { start.x , start.y };
	SDL_FPoint endPoint = { end.x , end.y };
	if (!SDL_PointInFRect(&startPoint, &this->camera) && !SDL_PointInFRect(&endPoint, &this->camera)) {
		return;
	}
	startPoint.x = startPoint.x - this->camera.x;
	startPoint.y = startPoint.y - this->camera.y;
	endPoint.x = endPoint.x - this->camera.x;
	endPoint.y = endPoint.y - this->camera.y;

	SDL_SetRenderDrawColor(renderer.get()
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.R()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.G()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.B()))
		, PrecisionRoundingoInt(std::lerp(UINT_8_BEGIN, UINT_8_END, color.A())));

	SDL_RenderDrawLineF(renderer.get()
		, startPoint.x
		, startPoint.y
		, endPoint.x
		, endPoint.y);
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

void RendererImpl::UpdateWindow()
{
	Uint32 window_flags = -1;

	switch (spic::window::SELECTOR)
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