#include "CollisionDetectionScript.h"

void CollisionDetectionScript::OnStart() {
	std::cout << "Script started for game object: " << this->gameObject->Tag() << std::endl;
}
void CollisionDetectionScript::OnUpdate() {
	
}
void CollisionDetectionScript::OnTriggerEnter2D(const spic::Collider& collider) {
	std::cout << "Collision enter" << std::endl;
}

void CollisionDetectionScript::OnTriggerExit2D(const spic::Collider& collider) {
	std::cout << "Collision exit" << std::endl;
}

void CollisionDetectionScript::OnTriggerStay2D(const spic::Collider& collider) {
}