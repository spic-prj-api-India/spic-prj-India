#include "GameObject.hpp"
#include "Component.hpp"
#include "Transform.hpp"
#include "RigidBody.hpp"
#include <string>
#include <vector>
#include <memory>
#include "Collider.hpp"
#include <functional>

using namespace spic;

GameObject::GameObject()
{}

std::string GameObject::Tag() const
{
	return tag;
}
std::shared_ptr<Transform>& GameObject::Transform()
{
	return transform;
}
void GameObject::Tag(std::string& _tag) {
	tag = _tag;
}
void GameObject::Transform(std::shared_ptr<spic::Transform> _transform)
{
	transform = _transform;
}

bool destroyOnLoad_ = true; // True by default

void DontDestroyOnLoad()
{
	destroyOnLoad_ = false;
}

void DontDestroyOnLoad(bool destroyOnLoad)
{
	destroyOnLoad_ = destroyOnLoad;
}