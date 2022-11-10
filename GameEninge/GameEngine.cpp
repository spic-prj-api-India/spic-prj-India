#include "GameEngine.hpp"

GameEngine* GameEngine::pinstance_{ nullptr };
std::mutex GameEngine::mutex_;

GameEngine::GameEngine() {
	_extensions = std::map<std::string, std::shared_ptr<extensions::IEngineExtension>>();
}

GameEngine::~GameEngine() {
}

GameEngine* GameEngine::GetInstance()
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (pinstance_ == nullptr)
	{
		pinstance_ = new GameEngine();
	}
	return pinstance_;
}