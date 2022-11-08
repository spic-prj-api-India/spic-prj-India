#include "GameObject.hpp"

namespace spic {
	GameObject::GameObject() {

	}
	std::string GameObject::GetTag() const {
		return tag;
	}
	std::unique_ptr<Transform>& GameObject::GetTranform() {
		return transform;
	}
	std::unique_ptr<RigidBody>& GameObject::GetRigidBody() {
		return rigidBody;
	}

	void GameObject::SetTag(std::string& tag) {
		tag = tag;
	}
	void GameObject::SetTransform(std::unique_ptr<Transform> transform) {
		transform = std::move(transform);
	}
	void GameObject::SetRigidBody(std::unique_ptr<RigidBody> rigidBody) {
		rigidBody = std::move(rigidBody);
	}
	void GameObject::SetCollider(Collider* collider) {
		collider = collider;
	}
}