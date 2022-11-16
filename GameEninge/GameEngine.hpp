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
			GameEngine(GameEngine&& other) noexcept = delete;
			void operator=(const GameEngine& other) = delete;
			GameEngine& operator=(GameEngine&& other) noexcept = delete;
			static GameEngine* GetInstance();

			internal::EntityManager* entityManager = internal::EntityManager::GetInstance();
			std::map<std::string, std::shared_ptr<Scene>> scenes;

			void SetActiveScene(std::string scene);

			std::weak_ptr<Scene> GetActiveScene();

			void LoadScene(std::weak_ptr<Scene> scene);

	};
}

#endif // GAMEENGINE_H_