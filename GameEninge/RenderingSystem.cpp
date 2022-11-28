#include "RenderingSystem.hpp"
#include "Renderer.hpp"

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
	{
		spic::internal::Rendering::Clean();
		spic::internal::Rendering::UpdateCamera(&currentScene.Camera());
		for (const auto& entity : entities) {
			spic::internal::Rendering::Draw(entity.get());
		}
		spic::internal::TileMap* tileMap = currentScene.TileMap();
		if(tileMap != nullptr)
			tileMap->Render();
		spic::internal::Rendering::Render();
	}
}