#include "RenderingSystem.hpp"
#include "Renderer.hpp"

namespace spic::internal::systems {
	RenderingSystem::RenderingSystem() 
	{}

	RenderingSystem::~RenderingSystem()
	{}

	void RenderingSystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities)
	{}

	void RenderingSystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		spic::internal::Rendering::Clean();
		for (const auto& entity : entities) {
			spic::internal::Rendering::Draw(entity.get());
		}
		currentScene.TileMap().Render();
		spic::internal::Rendering::Render();
	}
}