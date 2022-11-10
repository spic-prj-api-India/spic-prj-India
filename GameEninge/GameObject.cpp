#include "GameObject.hpp"

namespace spic {
	GameObject::GameObject() {

	}
	std::string GameObject::Tag() const {
		return tag;
	}
	std::shared_ptr<Transform>& GameObject::Transform() {
		return transform;
	}
	void GameObject::Tag(std::string& _tag) {
		tag = _tag;
	}
	void GameObject::Transform(std::shared_ptr<spic::Transform> _transform) {
		transform = _transform;
	}
}