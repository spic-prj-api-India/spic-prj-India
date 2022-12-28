#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <map>
#include <vector>
#include <memory>
#include <mutex>
#include "IEngineExtension.hpp"
#include "Scene.hpp"
#include "TypeHelper.hpp"
#include "ContainerHelper.hpp"
#include "Settings.hpp"
#include <functional>

namespace spic {
	/**
	 * @brief Format: [](){return new Scene()}	
	*/
	typedef std::function<spic::Scene*()> CreateSceneFunction;

	/**
	 * @brief Format: [](){return std::shared_ptr<spic::GameObject>}	
	*/
	typedef std::function<std::shared_ptr<spic::GameObject>()> CreateGameObjectFunction;

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

		std::vector<std::shared_ptr<extensions::IEngineExtension>> _extensions;

		/**
		 * @brief CreateGameObjectFunction format: [](){return std::shared_ptr<spic::GameObject>}	
		*/
		std::map<std::string, CreateGameObjectFunction> _types;
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
		*/
		template <typename T>
		void AddExtension(std::shared_ptr<T> extension);

		/**
		 * @brief Gets extension of type IEngineExtension.
		*/
		template <typename T>
		std::weak_ptr<T> GetExtension();

		/**
		 * @brief Gets extensions of type IEngineExtension.
		*/
		template <typename T>
		std::vector<std::weak_ptr<T>> GetExtensions();

		/**
		 * @brief Checks if extension exists.
		*/
		template <typename T>
		bool HasExtension();

		/**
		 * @brief removes extension from engine.
		*/
		template <typename T>
		void RemoveExtension();

		/*
		 * @brief Registers GameObject type in engine.
		*/
		template<typename T>
		void RegisterType();

		/*
		 * @brief Creates GameObject of type.s
		 * @param The typeName is the key in the types list.
		 * @return A newly created GameObject if the type does not exist. Otherwise, the GameObject of the specified type will be returned.
		*/
		std::shared_ptr<spic::GameObject> CreateType(const std::string& typeName);

		/*
		 * @brief Register scene.
		 * @param sceneName The key in the scenes list.
		 * @param scene Function that creates scene.
		 *			Format: [](){return new Scene()}		
		*/
		void RegisterScene(const std::string& sceneName, CreateSceneFunction scene);

		/*
		 * @brief Load the specified scene.
		 * @details Destoys the current scene and sets it to this one even if this scene is already loaded
		 * @param scene The scene you want to load.
		 * @param sceneName Name of the scene
		*/
		void LoadScene(std::shared_ptr<Scene> scene);

		/*
		 * @brief Load the specified scene.
		 * @param sceneName: The name of the scene you want to load.
		*/
		void LoadSceneByName(const std::string& sceneName);

		/*
		 * @brief Save the current scene.
		 * @param fileName: The file name.
		*/
		void SaveScene(const std::string& fileName);

		/*
		@brief Load the specified scene.
		@param sceneName: The name of the scene you want to load.
		@param fileName: The file name.
		*/
		void LoadSceneBySaveFile(const std::string& sceneName, const std::string& fileName);

		/*
		 * @brief Destroy the current scene.
		 * @param forceDelete: Whether you also want to delete all GameObjects in the scene which are set to not be destroyed on load.
		*/
		void DestroyScene(bool forceDelete);

		/*
		 * @brief Gets active scene.
		 * @returns The current scene.
		*/
		std::shared_ptr<Scene> GetActiveScene();

		/*
		 * @brief Gets scene with name.
		 * @param The sceneName of the scene.
		 * @returns The scene with the given sceneName.
		*/
		std::shared_ptr<Scene> GetSceneByName(const std::string& sceneName);

		/*
		 * @brief Start game loop
		*/
		void Start();

		/*
		 * @brief Stop game loop
		*/
		void Quit();
	};

	template <typename T>
	void GameEngine::AddExtension(std::shared_ptr<T> extension)
	{
		if (HasExtension<T>())
			return;
		_extensions.emplace_back(extension);
	}

	template <typename T>
	std::weak_ptr<T> GameEngine::GetExtension()
	{
		for (const auto& extension : _extensions) {
			if (helper_functions::type_helper::SharedPtrIsOfType<T>(extension))
				return helper_functions::type_helper::CastSharedPtrToWeakType<T>(extension);
		}
		return std::dynamic_pointer_cast<T>(std::make_shared<extensions::IEngineExtension>());
	}

	template <typename T>
	std::vector<std::weak_ptr<T>>  GameEngine::GetExtensions()
	{
		std::vector<std::weak_ptr<T>> extensions;
		for (const auto& extension : _extensions) {
			if (helper_functions::type_helper::SharedPtrIsOfType<T>(extension))
				extensions.emplace_back(helper_functions::type_helper::CastSharedPtrToWeakType<T>(extension));
		}
		return extensions;
	}

	template <typename T>
	bool GameEngine::HasExtension()
	{
		for (const auto& extension : _extensions) {
			if (helper_functions::type_helper::SharedPtrIsOfType<T>(extension))
				return true;
		}
		return false;
	}

	template <typename T>
	void GameEngine::RemoveExtension()
	{
		auto findFunction = [](std::shared_ptr<extensions::IEngineExtension> ext) {
			return helper_functions::type_helper::SharedPtrIsOfType<T>(ext);
		};
		std::shared_ptr<T> deletePtr = helper_functions::container::FindAndConvert<T>(_extensions, findFunction);
		_extensions.erase(deletePtr);
		do {
			deletePtr.reset();
		} while (deletePtr.use_count() != 0);
	}

	template<typename T>
	void GameEngine::RegisterType()
	{
		const std::string typeName = helper_functions::type_helper::GetTypeName<T>();
		if (_types.count(typeName) != 0)
			throw std::exception("Type is already registered.");
		const std::function createInstance = GameObject::CreateInstance<T>;
		_types[typeName] = createInstance;
	}
}

#endif // GAMEENGINE_H_