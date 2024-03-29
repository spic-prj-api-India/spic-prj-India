#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Component.hpp"
#include "Transform.hpp"
#include <string>
#include <vector>
#include <memory>
#include "TypeHelper.hpp"
#include <map>

namespace spic {
	/*
	 * @brief Forward declaration is used, because there is a circular dependency.
	*/
	class Component;

	/**
	 * @brief Any object which should be represented on screen.
	*/
	class GameObject {
	public:
		GameObject();

		/**
		 * @brief Constructor.
		 * @details Object will be created with name
		 * @param name The name for the game object.
		 * @spicapi
		*/
		GameObject(const std::string& name);

		GameObject(const GameObject& other) = default;
		GameObject(GameObject&& other) = default;
		virtual GameObject& operator=(const GameObject& other) = default;
		virtual GameObject& operator=(GameObject&& other) = default;

		/**
		 * @brief Needs to declare virtual destructor,
		 *			otherwise can't be casted to derived class
		 */
		virtual ~GameObject() = default;

		/**
		 * @brief Create instance function is used to 
		 *			create derived classes of the game object in the engine.
		 */
		template<typename T>
		static std::shared_ptr<T> CreateInstance()
		{
			return std::make_shared<T>();
		}

		/**
		 * @brief Checks if name exists in colection
		 * @param gameobjects 
		 * @param name 
		 * @return Returns if name exist
		*/
		static bool CheckIfNameExists(const std::vector<std::shared_ptr<GameObject>> objects, const std::string& name);

		/**
		 * @brief Sets content of gameobject
		 * @details If you want to use networking use this
		 * @param data 
		*/
		virtual void SetContent(std::map<std::string, std::string>& data);
		
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
		void Tag(const std::string& newTag);

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
		void Active(const bool flag);

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
		void Layer(const int newLayer);

		/**
		 * @brief Returns transform of GameObject.
		 * @return nullptr or transform.
		 * @spicapi
		 */
		std::shared_ptr<Transform> Transform() const;

		/**
		 * @brief Adds x and y of parent to transform of GameObject.
		 * @return Transform used for rendering
		 * @sharedapi
		 */
		spic::Transform RealTransform() const;

		/**
		 * @brief Sets tranform of GameObject.
		 * @param transform Desired value.
		 * @spicapi
		 */
		void Transform(std::shared_ptr<spic::Transform> transform);

		/**
		 * @brief const version of getting position
		 * @return
		*/
		const Point Position() const;

		/**
		 * @brief Const version of getting rotation
		 * @return
		*/
		const float Rotation() const;

		/**
		 * @brief Const version of scale
		 * @return
		*/
		const float Scale() const;

		/*
		* @brief Set this GameObject to get destroyed upon loading a new scene.
		* @sharedapi
		*/
		bool DestroyOnLoad() const;

		/*
		* @brief Set this GameObject to (not) get destroyed upon loading a new scene.
		* @param destroyOnLoad: Wether you want to set this GameObject to be destroyed or not upon loading a new scene.
		* @sharedapi
		*/
		void DestroyOnLoad(bool destroyOnLoad);

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
		 * @param name The name of the GameObject to be destroyed.
		 * @sharedapi
		 */
		static void Destroy(const std::string& name);

		/**
		 * @brief Removes a Component.
		 * @details Will search for the Component among the GameObjects.
		 * @param obj The Component to be removed. If obj == nullptr, Destroy() does nothing.
		 * @details TODO needs recursion
		 * @spicapi
		 */
		static void Destroy(Component* obj);

		/**
		* @brief Create function.
		* @details The new GameObject will be added to a statically
		*          available collection.  This makes the
		*          Find()-functions possible.
		* @param gameObject The game object.
		* @spicapi
		*/
		static void Create(const std::shared_ptr<GameObject> gameObject);

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


		/**
		 * @brief Compare two gameObjects (used for sort function)
		 * @param other The other object to compare this one with
		 * @return True if its less then other gameobject, false otherwise
		*/
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
		void AddComponent(std::shared_ptr<T> component);

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

		/**
		 * @brief Adds a gameobject to an gameobject
		 * @tparam T Has to be of type gameobject
		 * @param gameObject
		*/
		template<class T>
		void AddChild(std::shared_ptr<T> gameObject);

		/**
		 * @brief Gets first child with given type
		 * @return GameObject of type T
		 * @spicapi
		*/
		template<class T>
		std::shared_ptr<T> GetChild() const;

		/**
		 * @brief Gets all the children of this object
		 * @param includeInactive If you want to include inactive children
		 * @return A vector of gameobjects
		*/
		std::vector<std::shared_ptr<GameObject>> GetChildren(bool includeInactive = false) const;

		/**
		 * @brief Gets the current parent
		 * @return A pointer to the current parent
		*/
		const GameObject* GetParent() const;
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
		GameObject* parent;
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
	void GameObject::AddComponent(std::shared_ptr<T> component)
	{
		const auto parent = component->Parent();
		if (parent == nullptr)
		{
			component->Parent(*this);
			components.emplace_back(component);
		}
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

	template<class T>
	void GameObject::AddChild(std::shared_ptr<T> gameObject) {
		if (gameObject->GetParent() != nullptr)
			throw std::exception("Child can only have one parent");
		children.emplace_back(gameObject);
		gameObject->parent = this;
	}

	template<class T>
	std::shared_ptr<T> GameObject::GetChild() const
	{
		for (const auto& child : GetChildren()) {
			std::shared_ptr<T> castedChild = std::dynamic_pointer_cast<T>(child);
			bool isChild = castedChild != nullptr;
			if (isChild)
				return castedChild;
		}
		return nullptr;
	}
}

#endif // GAMEOBJECT_H_