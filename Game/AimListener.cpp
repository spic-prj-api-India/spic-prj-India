#include "AimListener.h"
#include "Input.hpp"
#include "GeneralHelper.hpp"
#include <Flock.hpp>
#include <BoxCollider.hpp>
#include <RigidBody.hpp>

AimListener::AimListener(const std::shared_ptr<spic::GameObject>& weapon) : rocketCount { 0 }
{
	this->followMouseListener = std::make_shared<FollowMouseListener>();
	this->weapon = weapon;
	this->angle = weapon->Transform()->rotation;

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
	float angleDeg = spic::GeneralHelper::RAD2DEG<float>(this->angle) + 90.0f;

	std::shared_ptr<spic::Flock> rocket = std::make_shared<spic::Flock>(spic::FlockBehaviour::SEEK, 0.05f, 2.0f);
	std::string rocketName = "Rocket" + std::to_string(rocketCount);
	std::string rocketTag = "rocket";
	std::shared_ptr<spic::Transform> rocketTransform = std::make_shared<spic::Transform>();
	rocketTransform->position = weapon->Transform()->position;
	rocketTransform->rotation = spic::GeneralHelper::DEG2RAD<float>(angleDeg);
	rocketTransform->scale = 0.125f;
	std::shared_ptr<spic::BoxCollider> rocketCollider = std::make_shared<spic::BoxCollider>();
	rocketCollider->Width(25.5f);
	rocketCollider->Height(75.0f);
	std::shared_ptr<spic::RigidBody> rocketRigidBody = std::make_shared<spic::RigidBody>(0.75f, 1.0f, spic::BodyType::dynamicBody);
	auto rocketSprite = std::make_shared<spic::Sprite>("assets/textures/missile.png", 1);

	/*rocket->Seperation(1.5f);
	rocket->Alignment(1.5f);
	rocket->Cohesion(1.5f);*/
	rocket->StartFlock();

	rocket->Name(rocketName);
	rocket->Tag(rocketTag);
	rocket->Transform(rocketTransform);
	rocket->AddComponent<spic::BoxCollider>(rocketCollider);
	rocket->AddComponent<spic::RigidBody>(rocketRigidBody);
	rocket->AddComponent<spic::Sprite>(rocketSprite);
	spic::GameObject::Create(rocket);
	followMouseListener->AddFollower(rocket);

	spic::Point mousePosition = spic::Input::MousePosition();
	spic::Point weaponPosition = weapon->Transform()->position;
	spic::Point force{};
	force.x = weaponPosition.x - mousePosition.x;
	force.y = weaponPosition.y - mousePosition.y;
	force.Normalize();
	rocketRigidBody->AddForce(force);
}