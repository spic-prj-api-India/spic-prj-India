#include "Rocket.h"
#include <BoxCollider.hpp>
#include <Sprite.hpp>
#include <Flocking.hpp>
#include <Steering.hpp>

Rocket::Rocket(const std::string& name) : GameObject(name)
{
	SetAttributes();
}

void Rocket::SetAttributes()
{
	Tag("rocket");
	AddComponent<spic::Sprite>(std::make_shared<spic::Sprite>("assets/textures/missile.png", 1));
}