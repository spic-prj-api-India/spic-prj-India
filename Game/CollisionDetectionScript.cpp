#include "CollisionDetectionScript.h"
#include "RocketSendScript.h"
#include <GameEngine.hpp>
#include "GameStatusSendScript.h"

void CollisionDetectionScript::OnTriggerEnter2D(const spic::Collider& collider) {
	std::cout << "Collision enter" << std::endl;
	if (collider.gameObject->Tag() == "obstacle") {
		gameObject->GetComponent<RocketSendScript>()->Destroy(DestroyType::OBSTACLE);
		spic::GameObject::Destroy(gameObject->Name());
	}
	if (collider.gameObject->Tag() == "player" && collider.gameObject->Name() == "Target") {
		spic::GameObject::Destroy(gameObject->Name());
		const auto& shooter = spic::GameObject::Find("Shooter");
		shooter->GetComponent<GameStatusSendScript>()->SetGameStatus(GameStatus::WON);
	}
}

void CollisionDetectionScript::OnTriggerExit2D(const spic::Collider& collider) {
	std::cout << "Collision exit" << std::endl;
}

void CollisionDetectionScript::OnTriggerStay2D(const spic::Collider& collider) {
}