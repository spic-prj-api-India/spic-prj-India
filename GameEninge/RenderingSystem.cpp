#include "RenderingSystem.hpp"

namespace spic::internal::systems {
	RenderingSystem::RenderingSystem() 
	{
	}

	RenderingSystem::~RenderingSystem()
	{
	}

	void RenderingSystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities)
	{}

	void RenderingSystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{}
}