#include "LoadingAnimation.h"
#include <Text.hpp>
#include <Animator.hpp>

LoadingAnimation::LoadingAnimation(const std::string& name, const spic::Point& position, const std::string& loadingText, const bool active) : GameObject(name)
{
	SetAttributes(position, loadingText, active);
}

void LoadingAnimation::SetAttributes(const spic::Point& position, const std::string& _loadingText, const bool active)
{
	Tag("animation");
	Active(active);
	Transform(std::make_shared<spic::Transform>(position, 0.0f, 1.0f));

	int fontSize = _loadingText.size() <= 20 ? 50 : 34;
	auto loadingText = std::make_shared<spic::Text>(600.0f, 400.0f
		, _loadingText
		, ""
		, fontSize
		, spic::Alignment::CENTER
		, spic::Color::white());
	loadingText->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));

	auto animatorObject = std::make_shared<spic::GameObject>();
	const float y = _loadingText.size() <= 20 ? 7.5f : 0.0f;
	animatorObject->Transform(std::make_shared<spic::Transform>(spic::Point(600.0f, y), 0.0f, .25f));
	auto animator = std::make_shared<spic::Animator>(60);
	animator->InitSpriteSheet("assets/textures/load_spritesheet.png", 4, 12, 188, 188);
	animator->Play(true);
	animatorObject->AddComponent(animator);

	AddChild(loadingText);
	AddChild(animatorObject);
}