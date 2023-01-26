#include "CollisionDetectionScript.h"

void CollisionDetectionScript::OnTriggerEnter2D(const spic::Collider& collider) {
	std::cout << "Collision enter " << collider.Parent()->Tag() << std::endl;
	if (collider.Parent()->Tag() == "obstacle" || collider.Parent()->Tag() == "alien") {
		spic::GameObject::Destroy(Parent()->Name());
	}
}

void CollisionDetectionScript::OnTriggerExit2D(const spic::Collider& collider) {
	std::cout << "Collision exit" << std::endl;
}

void CollisionDetectionScript::OnTriggerStay2D(const spic::Collider& collider) {
}
