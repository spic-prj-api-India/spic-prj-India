#include "RendererGameObjects.hpp"
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
#include "Settings.hpp"
#include "Debug.hpp"
#include "InternalTime.hpp"
#include "Time.hpp"

using namespace spic;
using namespace spic::internal::rendering;

namespace spic::internal::rendering::impl
{
	void RendererGameObjects::DrawGameObject(GameObject* gameObject, bool isUiOject)
	{
		// Only draws game object if it's active
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

	void RendererGameObjects::DrawSprites(GameObject* gameObject, const bool isUIObject)
	{
		using namespace spic::helper_functions::general_helper;

		const auto transform = gameObject->Transform();
		auto _sprites = gameObject->GetComponents<Sprite>();

		std::sort(_sprites.begin(), _sprites.end(), SpriteSorting);

		UIObject* uiObject = nullptr;

		if (isUIObject)
			uiObject = spic::helper_functions::type_helper::CastPtrToType<UIObject>(gameObject);

		for (auto& sprite : _sprites)
		{
			if (isUIObject)
				DrawUISprite(uiObject->Width(), uiObject->Height(), sprite.get(), transform.get());
			else
				DrawSprite(sprite.get(), transform.get());
		}
	}

	void RendererGameObjects::DrawAnimators(GameObject* gameObject, const bool isUiObject)
	{
		auto _animator = gameObject->GetComponents<Animator>();

		for (auto& animator : _animator)
		{
			DrawAnimator(animator.get(), gameObject->Transform().get(), isUiObject);
		}
	}

	void RendererGameObjects::DrawAnimator(Animator* animator, const Transform* transform, const bool isUIObject)
	{
		if (!animator->IsRunning())
			return;

		auto sprites = animator->Sprites();

		using namespace spic::helper_functions::general_helper;

		std::sort(sprites.begin(), sprites.end(), SpriteSorting);

		const auto framesAmount = sprites.back()->OrderInLayer() + 1;
		using namespace spic::internal::time;

		uint64_t current = SDL_GetTicks();
		double dT = (current - animator->LastUpdate()) / InternalTime::averageFrameTimeMilliseconds;

		using namespace spic;

		if (dT > InternalTime::frameRate / (animator->Fps() * Time::TimeScale()) && !animator->IsFrozen())
		{
			animator->IncreaseIndex();
			animator->LastUpdate(current);
		}

		DrawSprite(sprites[animator->Index() - 1].get(), transform, isUIObject);
	}

	void RendererGameObjects::DrawUISprite(const float width, const float height, const Sprite* sprite, const Transform* transform)
	{
		if (transform == nullptr)
			return;


		SDL_Texture* texture = textures.lock()->LoadTexture(sprite->_Sprite());

		using namespace spic::helper_functions::general_helper;


		SDL_FRect dstRect = { transform->position.x
			, transform->position.y
			, width * transform->scale
			, height * transform->scale };

		
		if (!this->window.lock()->RectHasIntersectionWithWindow(dstRect))
			return;


		DrawSprite(sprite, transform, texture, &dstRect, NULL);
	}

	void RendererGameObjects::DrawSprite(const Sprite* sprite, const Transform* transform, bool isUiOject)
	{
		if (transform == nullptr)
			return;

		SDL_Texture* texture = textures.lock()->LoadTexture(sprite->_Sprite());
		auto textureSize = textures.lock()->GetTextureSize(texture);

		const float displayWidth = (sprite->DisplayWidth() == 0) ? textureSize.x : sprite->Width();
		const float displayHeight = (sprite->DisplayHeight() == 0) ? textureSize.y : sprite->Height();

		SDL_FRect dstRect = { transform->position.x
			, transform->position.y
			, displayWidth* transform->scale * window.lock()->GetScaling()
			, displayHeight* transform->scale * window.lock()->GetScaling() };

		using namespace spic::helper_functions::general_helper;

		const int width = static_cast<int>((sprite->Width() == 0) ? textureSize.x : sprite->Width());
		const int height = static_cast<int>((sprite->Height() == 0) ? textureSize.y : sprite->Height());

		SDL_Rect sourceRect = { PrecisionRoundingoInt(sprite->X())
			, PrecisionRoundingoInt(sprite->Y())
			, PrecisionRoundingoInt(width)
			, PrecisionRoundingoInt(height) };

		auto camera = this->window.lock()->GetWindowCamera();

		if (!isUiOject)
		{
			if (this->window.lock()->RectHasIntersectionWithCamera(dstRect))
				dstRect = { dstRect.x - camera.x
					, dstRect.y - camera.y
					, dstRect.w
					, dstRect.h };
			else
				return;
		}
		else if (isUiOject)
		{
			if (!this->window.lock()->RectHasIntersectionWithWindow(dstRect))
				return;
		}
		else
			return;

		DrawSprite(sprite, transform, texture, &dstRect, &sourceRect);
	}

	void RendererGameObjects::DrawSprite(const Sprite* sprite, const Transform* transform, SDL_Texture* texture, SDL_FRect* dstRect, SDL_Rect* sourceRect) 
	{
		const auto color = sprite->Color();

		this->textures.lock()->SetTextureColor(texture, color);

		SDL_RendererFlip flip = this->textures.lock()->GetFlip(sprite->FlipX(), sprite->FlipY());

		using namespace spic::helper_functions::general_helper;

		double angle = RAD2DEG<double>(transform->rotation);

		if (texture == nullptr) 
		{
			this->textures.lock()->RenderTexture(NULL, sourceRect, dstRect, angle, flip);
			spic::debug::LogError(SDL_GetError());
			return;
		}

		this->textures.lock()->RenderTexture(texture, sourceRect, dstRect, angle, flip);
	}

	void RendererGameObjects::DrawUI(UIObject* gameObject)
	{
		auto* castedUiObject = dynamic_cast<Text*>(gameObject);
		const bool thisIsTextObject = castedUiObject != nullptr;
		if (thisIsTextObject)
			DrawText(castedUiObject);
	}

	void RendererGameObjects::DrawText(Text* text)
	{
		const std::string  fontPath = text->Font();
		const char* filePath = fontPath.c_str();
		if (std::filesystem::exists(filePath))
		{
			auto font = this->text.lock()->LoadFont(fontPath, text->Size());
			auto transform = text->Transform().get();
			auto colour = this->textures.lock()->ConvertsColor(text->Color());
			std::string texts{ text->_Text() };
			text->Alignment();

			const spic::GameObject* parent = text->GetParent();
			const float x = transform->position.x + (parent != nullptr ? parent->Transform()->position.x : 0);
			const float y = transform->position.y + (parent != nullptr ? parent->Transform()->position.y : 0);
			this->text.lock()->RenderMultiLineText(font, texts, colour, x, y, text->Width(), text->Height(), 2, text->Alignment());
		}
	}

	RendererGameObjects::RendererGameObjects(std::weak_ptr<RenderTextures> textures, std::weak_ptr<RenderingWindow> window, std::weak_ptr<RenderingText> text)
	{
		this->text = std::move(text);
		this->window = std::move(window);
		this->textures = std::move(textures);
	}
}