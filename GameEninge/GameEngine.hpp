#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <map>
#include <regex>
#include <memory>
#include <mutex>
#include "Scene.hpp"
#include "EntityManager.hpp"


namespace spic
{
	/**
	 * @brief The main class of the engine, has multiple functions to configure engine and load scenes.
	 */
	class GameEngine {
		private:
			static GameEngine* pinstance_;
			static std::mutex mutex_;

		protected:
			GameEngine();
			~GameEngine();

		public:
			GameEngine(GameEngine& other) = delete;
			GameEngine(GameEngine&& other) = delete;
			void operator=(const GameEngine& other) = delete;
			GameEngine& operator=(GameEngine&& other) = delete;
			static GameEngine* GetInstance();

			/*
			@brief Load the specified scene.
			@param scene: The name of the scene you want to load. 
			*/
			void LoadScene(std::shared_ptr<Scene> scene);
			/*
			@brief Destroy the current scene.
			@param forceDelete: Whether you also want to delete all GameObjects in the scene which are set to not be destroyed on load.
			*/
			void DestroyScene(bool forceDelete);

			/*
			@brief Set a scene as the current scene. Loads the specified scene.
			@param scene: The scene you want to set.
			*/
			void SetActiveScene(std::string scene);

			/*
			@brief Get the current scene.
			@return A weak_ptr to the current scene.
			*/
			std::weak_ptr<Scene> GetActiveScene();

			/*
			@brief Get the scene by its name.
			@param sceneName: The name of the scene you want to get.
			@return A shared_ptr to the scene.
			*/
			std::shared_ptr<Scene> GetSceneByName(std::string sceneName);
	};
}

#endif // GAMEENGINE_H_