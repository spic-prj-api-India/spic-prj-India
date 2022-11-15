#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <map>
#include <regex>
#include <memory>
#include <mutex>

namespace spic {
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



	};
}

#endif // GAMEENGINE_H_