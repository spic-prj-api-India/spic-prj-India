#include "GameObject.hpp"
#include <algorithm>
#include "AudioSource.hpp"
#include "TypeHelper.hpp"
#include "EntityManager.hpp"

namespace spic {
	std::vector<std::shared_ptr<GameObject>> GameObject::GetGameObjects() {
		return spic::internal::EntityManager::GetInstance()->GetEntities();
	}

	GameObject::GameObject() : active{ true }, layer{ 0 }, parent{nullptr}
	{
	}

	GameObject::GameObject(const std::string& name) : name{name}, active{ true }, layer{ 0 }
	{}

	std::shared_ptr<GameObject> GameObject::Find(const std::string& name)
	{
		for (const auto& gameObject : spic::internal::EntityManager::GetInstance()->GetEntities()) {
			if (gameObject->name == name)
				return gameObject;
		}
		return nullptr;
	}

	std::vector<std::shared_ptr<GameObject>> GameObject::FindGameObjectsWithTag(const std::string& tag)
	{
		std::vector<std::shared_ptr<GameObject>> gameObjects;
		for (const auto& gameObject : spic::internal::EntityManager::GetInstance()->GetEntities()) {
			if (gameObject->active && gameObject->tag == tag)
				gameObjects.emplace_back(gameObject);
		}
		return gameObjects;
	}

	std::shared_ptr<GameObject> GameObject::FindWithTag(const std::string& tag)
	{
		for (const auto& gameObject : spic::internal::EntityManager::GetInstance()->GetEntities()) {
			if (gameObject->tag == tag)
				return gameObject;
		}
		return nullptr;
	}

	void GameObject::Destroy(std::shared_ptr<GameObject> obj)
	{
		spic::internal::EntityManager::GetInstance()->RemoveEntity(obj);
	}

	void GameObject::Destroy(Component* obj)
	{
		std::string typeName = spic::GetTypeName(obj);
		for (const auto& gameObject : spic::internal::EntityManager::GetInstance()->GetEntities()) {
			gameObject->components.erase(std::remove_if(gameObject->components.begin(), gameObject->components.end(), [typeName](std::shared_ptr<Component> component) {
				return typeName == spic::GetTypeName(component);
				}));
		}
	}

	GameObject::operator bool() {
		std::vector<std::shared_ptr<GameObject>> gameObjects;
		for (const auto& gameObject : spic::internal::EntityManager::GetInstance()->GetEntities()) {
			if (typeid(gameObject).name() == typeid(this).name())
				return true;
		}
		return false;
	}

	bool GameObject::operator!=(const GameObject& other) {
		return typeid(this) != typeid(other);
	}

	bool GameObject::operator==(const GameObject& other) {
		return typeid(this) == typeid(other);
	}

	bool GameObject::operator<(const GameObject& other) {
		return layer < other.layer;
	}

	std::string GameObject::Name() const {
		return name;
	}

	void GameObject::Name(const std::string& newName) {
		name = newName;
	}

	std::string GameObject::Tag() const {
		return tag;
	}

	void GameObject::Tag(std::string& newTag) {
		tag = newTag;
	}

	bool GameObject::Active() const {
		return active;
	}

	void GameObject::Active(bool flag) {
		for (const auto& child : GetChildren(flag)) {
			child->Active(flag);
			if (flag)
				child->PlayAudioClipsOnAwake();
		}
		if (flag)
			PlayAudioClipsOnAwake();
		active = flag;
	}

	void GameObject::PlayAudioClipsOnAwake()
	{
		for (const auto& audioSource : GetComponents<AudioSource>()) {
			if (audioSource->PlayOnAwake())
				audioSource->Play(audioSource->Loop());
		}
	}

	int GameObject::Layer() const {
		return layer;
	}

	void GameObject::Layer(int newLayer) {
		layer = newLayer;
	}

	std::shared_ptr<Transform> GameObject::Transform()
	{
		return transform;
	}

	void GameObject::Transform(std::shared_ptr<spic::Transform> _transform) 
	{
		transform = _transform;
	}

	const Point GameObject::Position() const
	{
		return transform->position;
	}

	const float GameObject::Rotation() const
	{
		return transform->rotation;
	}

	const float GameObject::Scale() const
	{
		return transform->scale;
	}

	bool GameObject::DontDestroyOnLoad()
	{
		return false;
	}

	void GameObject::DontDestroyOnLoad(bool destroy)
	{
		destroyOnLoad = destroy;
	}

	bool GameObject::IsActiveInWorld() const {
		if (!active)
			return false;
		return parent == nullptr || parent->IsActiveInWorld();
	}

	std::vector<std::shared_ptr<GameObject>> GameObject::GetChildren(bool includeInactive) const {
		if (includeInactive = true)
			return children;
		std::vector <std::shared_ptr<GameObject>> filtered;
		std::copy_if(children.begin(), children.end(), std::back_inserter(filtered), [](std::shared_ptr<GameObject> gameObject) {
			return gameObject->Active();
			});
		return filtered;
	}

	const GameObject* GameObject::GetParent() const {
		if(parent != nullptr)
			return parent;

		return NULL;
	};
}