#include "AimListener.h"
#include "Input.hpp"
#include <BoxCollider.hpp>
#include <RigidBody.hpp>
#include "Rocket.h"
#include <GeneralHelper.hpp>

AimListener::AimListener(std::shared_ptr<spic::GameObject> weapon) : rocketCount{ 0 }
{
	this->followMouseListener = std::make_shared<FollowMouseListener>();
	this->angle = weapon->Transform()->rotation;
	this->weapon = std::move(weapon);

	spic::Input::Subscribe(spic::Input::MouseButton::LEFT, this->followMouseListener);
}

void AimListener::OnMouseMoved() {
	const spic::Point& mousePosition = spic::Input::MousePosition();
	const spic::Point& weaponPosition = weapon->Transform()->position;
	const float deltaX = weaponPosition.x - mousePosition.x;
	const float deltaY = weaponPosition.y - mousePosition.y;
	const float angleDeg = (atan2(deltaY, deltaX) * 180.0000f) / 3.1416f;
	this->angle = spic::GeneralHelper::DEG2RAD<float>(angleDeg);
	this->weapon->Transform()->rotation = angle;
}

void AimListener::OnMouseClicked() {
	Shoot();
	rocketCount++;
}
void AimListener::OnMousePressed() {

}
void AimListener::OnMouseReleased() {

}

void AimListener::Shoot()
{
	const float angleDeg = spic::GeneralHelper::RAD2DEG<float>(this->angle) + 90.0f;
	const float desiredAngle = spic::GeneralHelper::DEG2RAD<float>(angleDeg);
	const std::string name = "Rocket" + std::to_string(rocketCount);
	std::shared_ptr<Rocket> rocket = std::make_shared<Rocket>(name, weapon->Transform()->position, desiredAngle);
	rocket->StartForceDrivenEntity();

	spic::GameObject::Create(rocket);
	followMouseListener->AddFollower(rocket);

	spic::Point mousePosition = spic::Input::MousePosition();
	spic::Point weaponPosition = weapon->Transform()->position;
	spic::Point force{};
	force.x = weaponPosition.x - mousePosition.x;
	force.y = weaponPosition.y - mousePosition.y;
	force.Normalize();
	rocket->rigidBody->AddForce(force);
}