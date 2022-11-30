#include "Button.hpp"
#include "Text.hpp"
#include "StringHelper.hpp"

namespace spic {
	Button::Button() : Button(0.0f, 0.0f)
	{
	}

	Button::Button(const float width, const float height, const std::string& text, Color color) : UIObject(width, height)
	{
		std::string defaultSpritePath = StringHelper::GetBasePath() + "\\assets\\textures\\UISprite.png";
		std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(defaultSpritePath, 0, 0, color);
		AddComponent(sprite);
		if (!text.empty()) {
			const std::shared_ptr<Text> textObject = std::make_shared<Text>(width, height, text);
			textObject->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
			AddChild(textObject);
		}
	}

	void Button::Click()
	{
		if (interactable && onClick)
			onClick();
	}

	void Button::OnClick(std::function<void()> callback)
	{
		onClick = callback;
	}
}