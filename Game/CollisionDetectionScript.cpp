#include "CollisionDetectionScript.h"

void CollisionDetectionScript::OnTriggerEnter2D(const spic::Collider& collider) {
	std::cout << "Collision enter " << collider.gameObject->Tag() << std::endl;
	if (collider.gameObject->Tag() == "obstacle" || collider.gameObject->Tag() == "alien") {
		spic::GameObject::Destroy(gameObject->Name());
	}
}

void CollisionDetectionScript::OnTriggerExit2D(const spic::Collider& collider) {
	std::cout << "Collision exit" << std::endl;
}

void CollisionDetectionScript::OnTriggerStay2D(const spic::Collider& collider) {
}
