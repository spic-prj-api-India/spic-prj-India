#include "CollisionDetectionScript.h"

void CollisionDetectionScript::OnStart() {

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
	std::cout << "Stay" << std::endl;
}