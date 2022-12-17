#include "RenderingSystem.hpp"
#include "Renderer.hpp"
#include "TypeHelper.hpp"
#include "Debug.hpp"
#include "BoxCollider.hpp"
#include "GameEngine.hpp"
#include "IPhysicsExtension.hpp"

namespace spic::internal::systems {
	RenderingSystem::RenderingSystem()
	{

	}

	RenderingSystem::~RenderingSystem()
	{

	}

	void RenderingSystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{

	}

	void RenderingSystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		spic::internal::Rendering::Clean();
		spic::internal::Rendering::UpdateCamera(&currentScene.Camera());
		auto filteredEntities = GetFilteredEntities(entities);
		const spic::TileMap* tileMap = currentScene.TileMap();

		if (tileMap != nullptr)
			tileMap->Render();

		for (const auto& entity : filteredEntities[0]) 
		{
			spic::internal::Rendering::Draw(entity.get());
		}

		for (const auto& entity : filteredEntities[1]) 
		{
			spic::internal::Rendering::Draw(entity.get());
		}

		if(Debug::DEBUG_MODE && Debug::COLLIDER_VISIBILITY)
			DrawColliders();
		spic::internal::Rendering::Render();
	}

	std::vector<std::vector<std::shared_ptr<spic::GameObject>>> RenderingSystem::GetFilteredEntities(const std::vector<std::shared_ptr<spic::GameObject>>& entities) const
	{
		std::vector<std::shared_ptr<spic::GameObject>> nonUIEntities;
		std::vector<std::shared_ptr<spic::GameObject>> uiEntities;
		for (const auto& entity : entities) {
			if (spic::TypeHelper::SharedPtrIsOfType<UIObject>(entity))
				uiEntities.emplace_back(entity);
			else
				nonUIEntities.emplace_back(entity);
		}

		return { nonUIEntities, uiEntities };
	}

	void RenderingSystem::DrawColliders()
	{
		GameEngine* engine = GameEngine::GetInstance();
		for (const auto& weakExtension : engine->GetExtensions<spic::extensions::IPhysicsExtension>()) {
			if (const auto& physicsExtension = weakExtension.lock())
				physicsExtension->DrawColliders();
		}
	}
}