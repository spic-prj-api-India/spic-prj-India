#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <map>
#include <memory>
#include <mutex>
#include "IEngineExtension.hpp"
#include "Scene.hpp"
#include "TypeHelper.hpp"
#include "WindowValues.hpp"
#include <functional>

namespace spic {
	/**
	 * @brief The main class of the engine, has multiple functions to configure engine and load scenes.
	 *				The GameEngine class implements a singleton pattern.
	 */
	class GameEngine {
	private:
		static GameEngine* pinstance_;
		static std::mutex mutex_;
	protected:
		GameEngine();
		~GameEngine();

		std::map<std::string, std::shared_ptr<spic::internal::extensions::IEngineExtension>> _extensions;
		std::map<std::string, std::function<std::shared_ptr<spic::GameObject>()>> _types;
		bool quit;
	public:
		GameEngine(GameEngine& other) = delete;
		GameEngine(GameEngine&& other) = delete;
		void operator=(const GameEngine& other) = delete;
		GameEngine& operator=(GameEngine&& other) = delete;
		static GameEngine* GetInstance();

		/**
		* @brief Adds extensions to engine.
		* @param extension A IEngineExtension is used by the engine to
		*        configure the base functionality of the engine
		* @spicapi
		*/
		template <typename T>
		void AddExtension(std::shared_ptr<T> extension)
		{
			_extensions[spic::internal::GetTypeName<T>()] = extension;
		}

		/**
		* @brief Gets extension of type IEngineExtension.
		* @spicapi
		*/
		template <typename T>
		std::weak_ptr<T> GetExtension()
		{
			return std::dynamic_pointer_cast<T>(_extensions[spic::internal::GetTypeName<T>()]);
		}

		/**
		* @brief Gets extensions of type IEngineExtension.
		* @spicapi
		*/
		template <typename T>
		std::vector<std::weak_ptr<T>> GetExtensions()
		{
			std::vector<std::weak_ptr<T>> extensions;
			for (const auto& extension : _extensions) {
				std::weak_ptr<T> weakExtension = std::dynamic_pointer_cast<T>(extension.second);
				bool isOfType = weakExtension.lock() != nullptr;
				if (isOfType)
					extensions.emplace_back(weakExtension);
			}
			return extensions;
		}

		/**
		* @brief Checks if extension exists.
		* @spicapi
		*/
		template <typename T>
		bool HasExtension()
		{
			return _extensions.count(spic::internal::GetTypeName<T>());
		}

		/**
		* @brief removes extension from engine.
		* @spicapi
		*/
		template <typename T>
		void RemoveExtension()
		{
			std::string typeName = spic::internal::GetTypeName<T>();
			std::shared_ptr<T> deletePtr = std::dynamic_pointer_cast<T>(_extensions[typeName]);
			_extensions.erase(typeName);
			do {
				deletePtr.reset();
			} while (deletePtr.use_count() != 0);
		}

		/*
		@brief Registers GameObject type in engine.
		*/
		template<typename T>
		void RegisterType() 
		{
			const std::string typeName = spic::internal::GetTypeName<T>();
			if (_types.count(typeName) != 0)
				throw std::exception("Type is already registered.");
			const std::function createInstance = GameObject::CreateInstance<T>;
			_types[typeName] = createInstance;
		}

		/*
		@brief Creates GameObject of type.
		@param The typeName is the key in the types list.
		*/
		std::shared_ptr<spic::GameObject> CreateType(const std::string& typeName);

		/*
		@brief Register scene.
		@param The sceneName is the key in the scenes list.
		@param The scene that will be registered in scenes list.
		*/
		void RegisterScene(const std::string& sceneName, std::shared_ptr<Scene> scene);

		/*
		@brief Load the specified scene.
		@param sceneName: The name of the scene you want to load.
		*/
		void SetActiveScene(const std::string& sceneName);

		/*
		@brief Load the specified scene.
		@param scene: The scene you want to load.
		*/
		void LoadScene(std::shared_ptr<Scene> scene);

		/*
		@brief Destroy the current scene.
		@param forceDelete: Whether you also want to delete all GameObjects in the scene which are set to not be destroyed on load.
		*/
		void DestroyScene(bool forceDelete);

		/*
		@brief Gets active scene.
		@returns The current scene.
		*/
		std::shared_ptr<Scene> GetActiveScene();

		/*
		@brief Gets scene with name.
		@param The sceneName of the scene.
		@returns The scene with the given sceneName.
		*/
		std::shared_ptr<Scene> GetSceneByName(const std::string& sceneName);

		/*
		* @brief Start game loop
		* @spicapi
		*/
		void Start(const spic::window::WindowValues* values);

		/*
		* @brief Stop game loop
		* @spicapi
		*/
		void Quit();
	private:
		/**
		* @brief Checks if type is of type IEngineExtension
		* @spicapi
		*/
		template <typename T>
		bool IsEngineExtension(std::shared_ptr<T> extension) const
		{
			auto castedEngineExtension = std::dynamic_pointer_cast<spic::internal::extensions::IEngineExtension>(extension);
			return castedEngineExtension != nullptr;
		}
	};
}

#endif // GAMEENGINE_H_