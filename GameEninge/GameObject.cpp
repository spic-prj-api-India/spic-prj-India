#include "GameObject.hpp"
#include <algorithm>
#include "AudioSource.hpp"
#include "TypeHelper.hpp"
#include "EntityManager.hpp"
#include <string>
#include "GeneralHelper.hpp"

namespace spic 
{
	std::vector<std::shared_ptr<GameObject>> GameObject::GetGameObjects()
	{
		return spic::internal::EntityManager::GetInstance()->GetEntities();
	}

	GameObject::GameObject() : active{ true }
		, layer{ 0 }, parent{ nullptr }
		, name{ spic::helper_functions::general_helper::GetRandomUUID() }, destroyOnLoad{ true }
	{
		components = {};
		Point position{ 0.0f, 0.0f };
		transform = std::make_shared<spic::Transform>(position, 0.0f, 1.0f);
	}

	void GameObject::Create(const std::shared_ptr<GameObject> gameObject)
	{
		internal::EntityManager::GetInstance()->AddEntity(std::move(gameObject));
	}

	GameObject::GameObject(const std::string& name) : active{ true }, layer{ 0 }, parent{ nullptr }, name{ name }, destroyOnLoad{ true }
	{
		components = {};
		Point position{ 0.0f, 0.0f };
		transform = std::make_shared<spic::Transform>(position, 0.0f, 1.0f);
	}

	std::shared_ptr<GameObject> FindRecursion(const std::vector<std::shared_ptr<GameObject>>& objects, const std::string& name)
	{
		for (const auto& gameObject : objects)
			if (gameObject->Name() == name)
				return gameObject;

		return nullptr;
	}

	std::shared_ptr<GameObject> GameObject::Find(const std::string& name)
	{
		for (const auto& gameObject : spic::internal::EntityManager::GetInstance()->GetEntities()) {
			if (gameObject->name == name)
				return gameObject;

			if (auto i = FindRecursion(gameObject->GetChildren(), name); i.get() != nullptr)
				return i;
		}
		return nullptr;
	}

	/**
	 * @brief Hulper function for gameobject which uses recursion
	 * @param objects List of gameobjects
	 * @param tag Objects of tag
	 * @return All objects which uses this tag
	*/
	std::vector<std::shared_ptr<GameObject>> FindGameObjectsWithTagRecursion(const std::vector<std::shared_ptr<GameObject>>& objects, const std::string& tag)
	{
		std::vector<std::shared_ptr<GameObject>> gameObjects;

		for (const auto& gameObject : objects)
			if (gameObject->Active() && gameObject->Tag() == tag)
				gameObjects.emplace_back(gameObject);

		return gameObjects;
	}

	std::vector<std::shared_ptr<GameObject>> GameObject::FindGameObjectsWithTag(const std::string& tag)
	{
		std::vector<std::shared_ptr<GameObject>> gameObjects;
		for (const auto& gameObject : spic::internal::EntityManager::GetInstance()->GetEntities())
		{

			if (gameObject->Active() && gameObject->Tag() == tag)
				gameObjects.emplace_back(gameObject);

			const auto temp = FindGameObjectsWithTagRecursion(gameObject->children, tag);

			std::copy(temp.begin(), temp.end(), back_inserter(gameObjects));
			gameObjects.emplace_back(gameObject);
		}
		return gameObjects;
	}

	/**
	 * @brief Hulper function for gameobject which uses recursion
	 * @param objects List of gameobjects
	 * @param tag Objects of tag
	 * @return The first object that uses this tag
	*/
	std::shared_ptr<GameObject> FindWithTagRecusion(const std::vector<std::shared_ptr<GameObject>>& objects, const std::string& tag)
	{
		for (const auto& gameObject : objects)
		{
			if (gameObject->Tag() == tag)
				return gameObject;

			if (auto i = FindWithTagRecusion(gameObject->GetChildren(), tag); i != nullptr)
				return i;
		}
		return nullptr;
	}

	std::shared_ptr<GameObject> GameObject::FindWithTag(const std::string& tag)
	{
		return FindWithTagRecusion(spic::internal::EntityManager::GetInstance()->GetEntities(), tag);
	}

	void GameObject::Destroy(const std::string& name)
	{
		spic::internal::EntityManager::GetInstance()->RemoveEntity(name);
	}

	void GameObject::Destroy(Component* obj)
	{
		std::string typeName = spic::helper_functions::type_helper::GetTypeName(obj);

		for (const auto& gameObject : spic::internal::EntityManager::GetInstance()->GetEntities())
		{
			gameObject->components.erase(std::remove_if(gameObject->components.begin()
				, gameObject->components.end(), [typeName](std::shared_ptr<Component> component)
				{
					return typeName == spic::helper_functions::type_helper::GetTypeName(component);
				}));
		}
	}

	GameObject::operator bool()
	{
		std::vector<std::shared_ptr<GameObject>> gameObjects;

		for (const auto& gameObject : spic::internal::EntityManager::GetInstance()->GetEntities())
			if (typeid(gameObject).name() == typeid(this).name())
				return true;

		return false;
	}

	bool GameObject::operator!=(const GameObject& other)
	{
		return typeid(this) != typeid(other);
	}

	bool GameObject::operator==(const GameObject& other)
	{
		return typeid(this) == typeid(other);
	}

	bool GameObject::operator<(const GameObject& other)
	{
		return layer < other.layer;
	}

	bool GameObject::CheckIfNameExists(const std::vector<std::shared_ptr<spic::GameObject>> objects, const std::string& name)
	{
		for (auto& object : objects)
		{
			if (object->Name() == name)
				return true;

			if (GameObject::CheckIfNameExists(std::move(object->GetChildren()), name))
				return true;
		}

		return false;
	}

	void GameObject::SetContent(std::map<std::string, std::string>& data)
	{
	}

	std::string GameObject::Name() const
	{
		return name;
	}

	void GameObject::Name(const std::string& newName)
	{
		if (this->name != newName && spic::internal::EntityManager::GetInstance()->CheckIfNameExists(newName))
			throw std::runtime_error("Name of current gameobject exists already");

		name = newName;
	}

	std::string GameObject::Tag() const {
		return tag;
	}

	void GameObject::Tag(const std::string& newTag) {
		tag = newTag;
	}

	bool GameObject::Active() const {
		return active;
	}

	void GameObject::Active(const bool flag) {
		for (const auto& child : GetChildren(flag))
		{
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
		for (const auto& audioSource : GetComponents<AudioSource>())
			if (audioSource->PlayOnAwake())
				audioSource->Play(audioSource->Loop());
	}

	int GameObject::Layer() const
	{
		return layer;
	}

	void GameObject::Layer(const int newLayer)
	{
		layer = newLayer;
	}

	std::shared_ptr<Transform> GameObject::Transform() const
	{
		return transform;
	}

	Transform GameObject::RealTransform() const
	{
		auto parent = this->parent;
		spic::Transform transform = {this->transform->position,this->transform->rotation, this->transform->scale };
		while (parent != nullptr) {
			transform.position += parent->Transform()->position;
			parent = parent->parent;
		}
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

	bool GameObject::DestroyOnLoad() const
	{
		return destroyOnLoad;
	}

	void GameObject::DestroyOnLoad(bool destroy)
	{
		destroyOnLoad = destroy;
	}

	bool GameObject::IsActiveInWorld() const
	{
		if (!active)
			return false;

		return parent == nullptr || parent->IsActiveInWorld();
	}

	std::vector<std::shared_ptr<GameObject>> GameObject::GetChildren(bool includeInactive) const
	{
		if (includeInactive = true)
			return children;

		std::vector <std::shared_ptr<GameObject>> filtered;

		std::copy_if(children.begin(), children.end(), std::back_inserter(filtered)
			, [](std::shared_ptr<GameObject> gameObject)
			{
				return gameObject->Active();
			});

		return filtered;
	}

	const GameObject* GameObject::GetParent() const
	{
		if (parent != nullptr)
			return parent;

		return NULL;
	};
}