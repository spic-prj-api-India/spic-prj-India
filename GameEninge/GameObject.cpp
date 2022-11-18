#include "GameObject.hpp"
#include <algorithm>
#include "AudioSource.hpp"

namespace spic {
	GameObject::GameObject() : active{true}, layer{0}
	{}

	GameObject::GameObject(const std::string& name) : name{name}
	{}

	std::shared_ptr<GameObject> GameObject::Find(const std::string& name)
	{
		//TODO Met entity manager game object ophalen
		return nullptr;
	}

	std::vector<std::shared_ptr<GameObject>> GameObject::FindGameObjectsWithTag(const std::string& tag)
	{
		//TODO Met entity manager game object ophalen
		return std::vector<std::shared_ptr<GameObject>>();
	}

	std::shared_ptr<GameObject> GameObject::FindWithTag(const std::string& tag)
	{
		//TODO Met entity manager game object ophalen
		return nullptr;
	}

	void GameObject::Destroy(std::shared_ptr<GameObject> obj)
	{
		//TODO Met entity manager game object verwijderen
	}

	void GameObject::Destroy(Component* obj)
	{
		//TODO met entity manager de component verwijderen in alle game objects
	}

	GameObject::operator bool() {
		//TODO check of game object bestaat in entity manager
		return true;
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


	void GameObject::DontDestroyOnLoad()
	{
		destroyOnLoad = false;
	}

	void GameObject::DontDestroyOnLoad(bool destroy)
	{
		destroyOnLoad = destroy;
	}

	std::string GameObject::Tag() const 
	{
		return tag;
	}

	std::shared_ptr<Transform>& GameObject::Transform() 
	{
		return transform;
	}

	bool GameObject::Active() const {
		return active;
	}

	void GameObject::Tag(std::string& _tag) {
		tag = _tag;
	}

	void GameObject::Transform(std::shared_ptr<spic::Transform> _transform) 
	{
		transform = _transform;
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

	bool GameObject::IsActiveInWorld() const {
		if (!active)
			return false;
		std::shared_ptr<GameObject> parent = parent;
		while (parent != nullptr) {
			if (!parent->Active())
				return false;
			parent = parent->GetParent();
		}
		return true;
	}

	void GameObject::AddChild(const std::shared_ptr<spic::GameObject>& gameObject) {
		if (gameObject->GetParent() != nullptr)
			throw std::exception("Child can only have one parent");
		children.emplace_back(gameObject);
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

	std::shared_ptr<GameObject> GameObject::GetParent() const {
		return parent;
	};
}