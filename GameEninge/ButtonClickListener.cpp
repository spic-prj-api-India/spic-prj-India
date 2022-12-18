#include "ButtonClickListener.hpp"
#include "Input.hpp"
#include "GameEngine.hpp"
#include "GeneralHelper.hpp"

namespace spic::internal {
	ButtonClickListener::ButtonClickListener()
	{
		buttons;
	}

	void ButtonClickListener::OnMouseMoved()
	{
	}

	void ButtonClickListener::OnMouseClicked()
	{
		spic::Point point = spic::input::MousePosition();
		Rect mouseRect = {
			point.x,
			point.y,
			1.0f,
			1.0f
		};
		for (const auto& button : buttons) {
			const auto& transform = button->Transform();
			Rect buttonRect = {
				transform->position.x,
				transform->position.y,
				button->Width() * transform->scale,
				button->Height() * transform->scale
			};
			if (spic::general_helper::RectIntersection(mouseRect, buttonRect)) {
				button->Click();
				return;
			}
		}
	}

	void ButtonClickListener::OnMousePressed()
	{
	}

	void ButtonClickListener::OnMouseReleased()
	{
	}

	void ButtonClickListener::SetButtons(std::vector<std::shared_ptr<spic::Button>> buttons)
	{
		this->buttons = std::move(buttons);
	}
}