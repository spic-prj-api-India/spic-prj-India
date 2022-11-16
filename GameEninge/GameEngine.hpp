#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <map>
#include <regex>
#include <memory>
#include <mutex>
#include "Scene.hpp"
#include "EntityManager.hpp"

using namespace spic::internal;

namespace spic 
{
	/**
	 * @brief The main class of the engine, has multiple functions to configure engine and load scenes.
	 */
	class GameEngine {
		private:
			static GameEngine* pinstance_;
			static std::mutex mutex_;

			EntityManager* entityManager = EntityManager::GetInstance();

		protected:
			GameEngine();
			~GameEngine();

		public:
			GameEngine(GameEngine& other) = delete;
			GameEngine(GameEngine&& other) = delete;
			void operator=(const GameEngine& other) = delete;
			GameEngine& operator=(GameEngine&& other) = delete;
			static GameEngine* GetInstance();

			std::map<std::string, std::shared_ptr<Scene>> scenes;

			void LoadScene(std::shared_ptr<Scene> scene)
			{
				entityManager->SetScene(scene);
			}

			void SetActiveScene(std::string scene)
			{
				auto it = scenes.find(scene);
				LoadScene(it->second);
			}

			std::weak_ptr<Scene> GetActiveScene()
			{
				return entityManager->currentScene;
			}

	};
}

#endif // GAMEENGINE_H_