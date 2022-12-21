#include "AimListener.h"
#include "Input.hpp"
#include <BoxCollider.hpp>
#include <RigidBody.hpp>
#include "SeekingRocket.h"
#include <GeneralHelper.hpp>
#include "CollisionDetectionScript.h"
#include <Steering.hpp>
#include "RocketSendScript.h"
#include "Debug.hpp"
#include "ShooterSendScript.h"
#include <GameEngine.hpp>
#include "GameStatusSendScript.h"

using namespace spic::helper_functions::general_helper;

AimListener::AimListener(const spic::GameObject* weapon, std::shared_ptr<spic::Text> counter) : 
	rocketCount{ 0 }, maxRockets{ 5 }, angle{ weapon->Transform()->rotation }, sceneLoaded{false}
{
	this->weapon = weapon;
	this->counter = std::move(counter);
	this->counter->_Text("Rockets left: " + std::to_string(this->maxRockets-this->rocketCount));
}

void AimListener::OnMouseMoved() {
	if (weapon == nullptr)
		return;
	const spic::Point& mousePosition = spic::input::MousePosition();
	const spic::Point& weaponPosition = weapon->Transform()->position;
	const float deltaX = weaponPosition.x - mousePosition.x;
	const float deltaY = weaponPosition.y - mousePosition.y;
	const float angleDeg = (atan2(deltaY, deltaX) * 180.0000f) / 3.1416f;
	this->weapon->Transform()->rotation = DEG2RAD<float>(angleDeg);
}

void AimListener::OnMouseClicked() {
	if (weapon == nullptr)
		return;
	Shoot();
	rocketCount++;
	this->counter->_Text("Rockets left: " + std::to_string(this->maxRockets - this->rocketCount));
	CheckLoseCondition();
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

void AimListener::CheckLoseCondition()
{
	if (rocketCount > maxRockets && !sceneLoaded) {
		sceneLoaded = true;
		this->weapon->GetComponent<GameStatusSendScript>()->SetGameStatus(GameStatus::LOST);
	}
}