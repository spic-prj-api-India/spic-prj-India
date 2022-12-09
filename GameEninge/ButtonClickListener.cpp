#include "ButtonClickListener.hpp"
#include "Input.hpp"
#include "GameEngine.hpp"
#include <SDL2/SDL_rect.h>

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
		spic::Point point = spic::Input::MousePosition();
		SDL_FRect mouseRect = {
			point.x,
			point.y,
			1.0f,
			1.0f
		};
		for (const auto& button : buttons) {
			const auto& transform = button->Transform();
			SDL_FRect buttonRect = {
				transform->position.x,
				transform->position.y,
				button->Width() * transform->scale,
				button->Height() * transform->scale
			};
			if (SDL_HasIntersectionF(&mouseRect, &buttonRect)) {
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

	void ButtonClickListener::SetButtons(const  std::vector<std::shared_ptr<spic::Button>>& buttons)
	{
		this->buttons = buttons;
	}
}