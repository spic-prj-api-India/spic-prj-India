#include "NetCollisionDetectionScript.h"
#include "RocketSendScript.h"
#include <GameEngine.hpp>
#include "GameStatusSendScript.h"

void NetCollisionDetectionScript::OnTriggerEnter2D(const spic::Collider& collider) {
	std::cout << "Collision enter" << std::endl;
	if (collider.Parent()->Tag() == "obstacle") {
		gameObject->GetComponent<RocketSendScript>()->Destroy(DestroyType::OBSTACLE);
		spic::GameObject::Destroy(gameObject->Name());
	}
	if (collider.Parent()->Tag() == "player" && collider.Parent()->Name() == "Target") {
		spic::GameObject::Destroy(gameObject->Name());
		const auto& shooter = spic::GameObject::Find("Shooter");
		shooter->GetComponent<GameStatusSendScript>()->SetGameStatus(GameStatus::WON);
	}
}

void NetCollisionDetectionScript::OnTriggerExit2D(const spic::Collider& collider) {
	std::cout << "Collision exit" << std::endl;
}

void NetCollisionDetectionScript::OnTriggerStay2D(const spic::Collider& collider) {
}