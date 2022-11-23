#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Component.hpp"
#include "Transform.hpp"
#include "RigidBody.hpp"
#include <string>
#include <vector>
#include <memory>
#include "Collider.hpp"
#include "Sprite.hpp"

namespace spic {
	/**
	 * @brief Any object which should be represented on screen.
	 */
	class GameObject : public std::enable_shared_from_this<GameObject> {
	public:
		GameObject();
		/**
		 * @brief Needs to declare virtual destructor,
		 *			otherwise can't be casted to derived class
		 */
		virtual ~GameObject(){};
		GameObject(const GameObject& other) = default;
		GameObject(GameObject&& other) = default;
		GameObject& operator=(const GameObject& other) = default;
		GameObject& operator=(GameObject&& other) = default;

		/**
		 * @brief Returns name of GameObject.
		 * @return string.
		 * @spicapi
		 */
		std::string Name() const;

		/**
		 * @brief Sets name of GameObject.
		 * @param newName Desired value.
		 * @spicapi
		 */
		void Name(const std::string& newName);

		/**
		 * @brief Returns tag of GameObject.
		 * @return string.
		 * @spicapi
		 */
		std::string Tag() const;

		/**
		 * @brief Sets tag of GameObject.
		 * @param tag Desired value.
		 * @spicapi
		 */
		void Tag(std::string& newTag);

		/**
		 * @brief Returns whether this game object is itself active.
		 * @return true if active, false if not.
		 * @spicapi
		 */
		bool Active() const;

		/**
		 * @brief Activates/Deactivates the GameObject, depending on the given true or false value.
		 *			If flag is true, audio clips are triggered.
		 * @param active Desired value.
		 * @spicapi
		 */
		void Active(bool flag);

		/**
		 * @brief Returns layer of GameObject.
		 * @return int.
		 * @spicapi
		 */
		int Layer() const;

		/**
		 * @brief Sets layer of GameObject.
		 * @param newLayer Desired value.
		 * @spicapi
		 */
		void Layer(int newLayer);

		/**
		 * @brief Returns transform of GameObject.
		 * @return nullptr or transform.
		 * @spicapi
		 */
		std::shared_ptr<Transform> Transform();

		/**
		 * @brief Sets tranform of GameObject.
		 * @param transform Desired value.
		 * @spicapi
		 */
		void Transform(std::shared_ptr<spic::Transform> transform);

		/*
		@brief Set this GameObject to get destroyed upon loading a new scene.
		*/
		bool DontDestroyOnLoad();

		/*
		@brief Set this GameObject to (not) get destroyed upon loading a new scene.
		@param destroyOnLoad: Wether you want to set this GameObject to be destroyed or not upon loading a new scene.
		*/
		void DontDestroyOnLoad(bool destroyOnLoad);

		/**
		 * @brief Returns whether this game component is active, taking its parents
		 *        into consideration as well.
		 * @return true if game object and all of its parents are active,
		 *        false otherwise.
		 * @spicapi
		 */
		bool IsActiveInWorld() const;

		/**
		 * @brief Finds a GameObject by name and returns it.
		 * @param name The name of the GameObject you want to find.
		 * @return Pointer to GameObject, or nullptr if not found.
		 * @spicapi
		 */
		static std::shared_ptr<GameObject> Find(const std::string& name);

		/**
		 * @brief Returns a vector of active GameObjects tagged tag. Returns empty
		 *        vector if no GameObject was found.
		 * @param tag The tag to find.
		 * @return std::vector of GameObject pointers. No ownership.
		 * @spicapi
		 */
		static std::vector<std::shared_ptr<GameObject>> FindGameObjectsWithTag(const std::string& tag);

		/**
		 * @brief Returns one active GameObject tagged tag. Returns nullptr if no GameObject was found.
		 * @param tag The tag to find.
		 * @return Pointer to GameObject, or nullptr if not found.
		 * @spicapi
		 */
		static std::shared_ptr<GameObject> FindWithTag(const std::string& tag);

		/**
		 * @brief Returns the first active loaded object of type T.
		 * @spicapi
		 */
		template<class T>
		static std::shared_ptr<T> FindObjectOfType(bool includeInactive = false);

		/**
		 * @brief Gets a list of all loaded objects of type T.
		 * @spicapi
		 */
		template<class T>
		static std::vector<std::shared_ptr<T>> FindObjectsOfType(bool includeInactive = false);

		/**
		 * @brief Removes a GameObject from the administration.
		 * @details Child GameObjects will be destroyed, too, as well as
		 *          Components owned by the GameObject.
		 * @param obj The GameObject to be destroyed. Must be a valid pointer to existing Game Object.
		 * @exception A std::runtime_exception is thrown when the pointer is not valid.
		 * @spicapi
		 */
		static void Destroy(std::shared_ptr<GameObject> obj);

		/**
		 * @brief Removes a Component.
		 * @details Will search for the Component among the GameObjects.
		 * @param obj The Component to be removed. If obj == nullptr, Destroy() does nothing.
		 * @spicapi
		 */
		static void Destroy(Component* obj);

		/**
		 * @brief Constructor.
		 * @details Object will be created with name
		 * @param name The name for the game object.
		 * @spicapi
		 */
		GameObject(const std::string& name);

		/**
		 * @brief Does the object exist? TODO wat wordt hiermee bedoeld?
		 * @spicapi
		 */
		operator bool();

		/**
		 * @brief Compare two GameObjects.
		 * @param other The other object to compare this one with.
		 * @return true if not equal, false otherwise.
		 * @spicapi
		 */
		bool operator!=(const GameObject& other);

		/**
		 * @brief Compare two GameObjects
		 * @param other The other object to compare this one with.
		 * @return true if equal, false otherwise.
		 * @spicapi
		 */
		bool operator==(const GameObject& other);

		/// @brief Compare two gameObjects (used for sort function)
		/// @param other The other object to compare this one with
		/// @return True if its less then other gameobject, false otherwise
		bool operator<(const GameObject& other);

		template<class T>
		bool HasComponent() const;

		/**
		 * @brief Add a Component of the specified type. Must be a valid
		 *        subclass of Component. The GameObject assumes ownership of
		 *        the Component.
		 * @details This function places a pointer to the component in
		 *          a suitable container.
		 * @param component Reference to the component.
		 * @spicapi
		 */
		template<class T>
		void AddComponent(std::shared_ptr<Component> component);

		/**
		 * @brief Get the first component of the specified type. Must be
		 *        a valid subclass of Component.
		 * @return Pointer to Component instance.
		 * @spicapi
		 */
		template<class T>
		std::shared_ptr<T> GetComponent() const;

		/**
		 * @brief Get the first component of the specified type from
		 *        contained game objects. Must be
		 *        a valid subclass of Component.
		 * @return Pointer to Component instance.
		 * @spicapi
		 */
		template<class T>
		std::shared_ptr<T> GetComponentInChildren() const;

		/**
		 * @brief Get the first component of the specified type from
		 *        the parent game object. Must be
		 *        a valid subclass of Component.
		 * @return Pointer to Component instance.
		 * @spicapi
		 */
		template<class T>
		std::shared_ptr<Component> GetComponentInParent() const;

		/**
		 * @brief Get all components of the specified type. Must be
		 *        a valid subclass of Component.
		 * @return Vector with pointers to Component instances.
		 * @spicapi
		 */
		template<class T>
		std::vector<std::shared_ptr<T>> GetComponents() const;

		/**
		 * @brief Get all components of the specified type from
		 *        contained game objects. Must be
		 *        a valid subclass of Component.
		 * @return Vector with pointers to Component instances.
		 * @spicapi
		 */
		template<class T>
		std::vector<std::shared_ptr<T>> GetComponentsInChildren() const;

		/**
		 * @brief Get all components op the specified type from
		 *        the parent game object. Must be
		 *        a valid subclass of Component.
		 * @return Vector with pointers to Component instances.
		 * @spicapi
		 */
		template<class T>
		std::vector<std::shared_ptr<T>> GetComponentsInParent() const;

		void AddChild(const std::shared_ptr<spic::GameObject>& gameObject);

		/// @brief Gets all the children of this object
		/// @param includeInactive If you want to include inactive children  
		/// @return A vector of gameobjects
		std::vector<std::shared_ptr<GameObject>> GetChildren(bool includeInactive = false) const;

		/// @brief Gets all the children of this object
		/// @param includeInactive If you want to include inactive children  
		/// @return A vector of gameobjects
		std::shared_ptr<GameObject> GetParent() const;
	private:
		void PlayAudioClipsOnAwake();
		static std::vector<std::shared_ptr<GameObject>> GetGameObjects();
	private:
		std::string name;
		std::string tag;
		bool active;
		int layer;
		bool destroyOnLoad;
		std::shared_ptr<spic::Transform> transform;
		std::vector<std::shared_ptr<Component>> components;
		std::vector<std::shared_ptr<GameObject>> children;
		std::shared_ptr<GameObject> parent;
	};

	template<class T>
	std::shared_ptr<T> GameObject::FindObjectOfType(bool includeInactive) {
		for (const auto& gameObject : GetGameObjects()) {
			std::shared_ptr<T> castedGameObject = std::dynamic_pointer_cast<T>(gameObject);
			const bool isType = castedGameObject != nullptr;
			if ((includeInactive || gameObject->active) && isType)
				return castedGameObject;
		}
		return nullptr;
	}

	template<class T>
	std::vector<std::shared_ptr<T>> GameObject::FindObjectsOfType(bool includeInactive) {
		std::vector<std::shared_ptr<T>> gameObjects;
		for (const auto& gameObject : GetGameObjects()) {
			const bool isType = std::dynamic_pointer_cast<T>(gameObject) != nullptr;
			if ((includeInactive || gameObject->active) && isType)
				gameObjects.emplace_back(std::dynamic_pointer_cast<T>(gameObject));
		}
		return gameObjects;
	}

	template<class T>
	bool GameObject::HasComponent() const {
		for (const auto& component : components) {
			bool isComponent = std::dynamic_pointer_cast<T>(component) != nullptr;
			if (isComponent)
				return true;
		}
		return false;
	}

	template<class T>
	void GameObject::AddComponent(std::shared_ptr<Component> component)
	{
		components.emplace_back(component);
	}

	template<class T>
	std::shared_ptr<T> GameObject::GetComponent() const
	{
		for (const auto& component : components) {
			std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component);
			bool isComponent = castedComponent != nullptr;
			if (isComponent)
				return castedComponent;
		}
		return nullptr;
	}

	template<class T>
	std::shared_ptr<T> GameObject::GetComponentInChildren() const {
		for (const auto& child : GetChildren()) {
			std::shared_ptr<T> component = child->GetComponent<T>();
			if (component != nullptr)
				return component;
		}
		return nullptr;
	}

	template<class T>
	std::shared_ptr<Component> GameObject::GetComponentInParent() const {
		return parent->GetComponent<T>();
	}

	template<class T>
	std::vector<std::shared_ptr<T>> GameObject::GetComponents() const {
		std::vector<std::shared_ptr<T>> filteredComponents = std::vector<std::shared_ptr<T>>();
		for (const auto& component : components) {
			std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component);
			bool isComponent = castedComponent != nullptr;
			if (isComponent)
				filteredComponents.emplace_back(castedComponent);
		}
		return filteredComponents;
	}

	template<class T>
	std::vector<std::shared_ptr<T>> GameObject::GetComponentsInChildren() const {
		for (const auto& child : GetChildren()) {
			std::shared_ptr<T> component = child->GetComponents<T>();
			if (component != nullptr)
				return component;
		}
		return nullptr;
	}

	template<class T>
	std::vector<std::shared_ptr<T>> GameObject::GetComponentsInParent() const {
		return parent->GetComponents<T>();
	}
}

#endif // GAMEOBJECT_H_
