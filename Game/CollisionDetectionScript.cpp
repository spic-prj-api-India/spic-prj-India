#include "CollisionDetectionScript.h"
#include "RocketSendScript.h"

void CollisionDetectionScript::OnTriggerEnter2D(const spic::Collider& collider) {
	std::cout << "Collision enter" << std::endl;
	if (collider.gameObject->Tag() == "obstacle") {
		gameObject->GetComponent<RocketSendScript>()->Destroy(DestroyType::OBSTACLE);
		spic::GameObject::Destroy(gameObject->Name());
	}
}

void CollisionDetectionScript::OnTriggerExit2D(const spic::Collider& collider) {
	std::cout << "Collision exit" << std::endl;
}

void CollisionDetectionScript::OnTriggerStay2D(const spic::Collider& collider) {
}