#include "AimListener.h"
#include "Input.hpp"
#include <BoxCollider.hpp>
#include <RigidBody.hpp>
#include "SeekingRocket.h"
#include <GeneralHelper.hpp>
#include "CollisionDetectionScript.h"
#include <Steering.hpp>
#include "RocketSendScript.h"

using namespace spic::helper_functions::general_helper;

AimListener::AimListener(const std::string& entityName) : rocketCount{ 0 }
{
	this->weapon = std::move(spic::GameObject::Find(entityName));
	this->angle = this->weapon->Transform()->rotation;
}

void AimListener::OnMouseMoved() {
	const spic::Point& mousePosition = spic::input::MousePosition();
	const spic::Point& weaponPosition = weapon->Transform()->position;
	const float deltaX = weaponPosition.x - mousePosition.x;
	const float deltaY = weaponPosition.y - mousePosition.y;
	const float angleDeg = (atan2(deltaY, deltaX) * 180.0000f) / 3.1416f;
	this->angle = DEG2RAD<float>(angleDeg);
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
	const auto& targetObject = spic::GameObject::Find("Target");
	if (targetObject != nullptr) {
		const float angleDeg = RAD2DEG<float>(this->angle) + 90.0f;
		const float desiredAngle = DEG2RAD<float>(angleDeg);
		const std::string name = "Rocket" + std::to_string(rocketCount);
		std::shared_ptr<SeekingRocket> rocket = std::make_shared<SeekingRocket>(name, weapon->Transform()->position, desiredAngle);
		rocket->AddComponent<spic::BehaviourScript>(std::make_shared<CollisionDetectionScript>());
		rocket->AddComponent<spic::SocketScript>(std::make_shared<RocketSendScript>());
		rocket->StartForceDrivenEntity();

		const auto& steering = rocket->GetComponent<spic::Steering>();
		steering->AddTarget(spic::TargetBehaviour::SEEK, targetObject->Transform()->position, 1.0f);

		spic::GameObject::Create(rocket);

		const spic::Point mousePosition = spic::input::MousePosition();
		const spic::Point weaponPosition = weapon->Transform()->position;
		spic::Point force{};
		force.x = weaponPosition.x - mousePosition.x;
		force.y = weaponPosition.y - mousePosition.y;
		force.Normalize();
		force *= 0.5f;
		rocket->rigidBody->AddForce(force);
	}
}