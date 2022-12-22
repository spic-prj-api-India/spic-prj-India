#include "NetAimListener.h"
#include "Input.hpp"
#include "SeekingRocket.h"
#include <GeneralHelper.hpp>
#include "NetCollisionDetectionScript.h"
#include "RocketSendScript.h"
#include "ShooterSendScript.h"
#include "GameStatusSendScript.h"
#include <Steering.hpp>

using namespace spic::helper_functions::general_helper;

NetAimListener::NetAimListener(const spic::GameObject* weapon, std::shared_ptr<spic::Text> counter) :
	rocketCount{ 0 }, maxRockets{ 5 }, angle{ weapon->Transform()->rotation }, sceneLoaded{false}
{
	this->weapon = weapon;
	this->counter = std::move(counter);
	this->counter->_Text("Rockets left: " + std::to_string(this->maxRockets-this->rocketCount));
}

void NetAimListener::OnMouseMoved() {
	if (weapon == nullptr)
		return;
	const spic::Point& mousePosition = spic::input::MousePosition();
	const spic::Point& weaponPosition = weapon->Transform()->position;
	const float deltaX = weaponPosition.x - mousePosition.x;
	const float deltaY = weaponPosition.y - mousePosition.y;
	const float angleDeg = (atan2(deltaY, deltaX) * 180.0000f) / 3.1416f;
	this->weapon->Transform()->rotation = DEG2RAD<float>(angleDeg);
}

void NetAimListener::OnMouseClicked() {
	if (weapon == nullptr)
		return;
	Shoot();
	rocketCount++;
	this->counter->_Text("Rockets left: " + std::to_string(this->maxRockets - this->rocketCount));
	CheckLoseCondition();
}

void NetAimListener::OnMousePressed() {

}

void NetAimListener::OnMouseReleased() {

}

void NetAimListener::Shoot()
{
	const auto& targetObject = spic::GameObject::Find("Target");
	if (targetObject != nullptr) {
		const float angleDeg = RAD2DEG<float>(this->angle) + 90.0f;
		const float desiredAngle = DEG2RAD<float>(angleDeg);
		const std::string name = "Rocket" + std::to_string(rocketCount);
		std::shared_ptr<SeekingRocket> rocket = std::make_shared<SeekingRocket>(name, weapon->Transform()->position, desiredAngle);
		rocket->AddComponent<spic::BehaviourScript>(std::make_shared<NetCollisionDetectionScript>());
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

void NetAimListener::CheckLoseCondition()
{
	if (rocketCount > maxRockets && !sceneLoaded) {
		sceneLoaded = true;
		this->weapon->GetComponent<GameStatusSendScript>()->SetGameStatus(GameStatus::LOST);
	}
}