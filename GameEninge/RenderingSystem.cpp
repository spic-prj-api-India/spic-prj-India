#include "RenderingSystem.hpp"
#include "Renderer.hpp"
#include "TypeHelper.hpp"
#include "Debug.hpp"
#include "BoxCollider.hpp"

namespace spic::internal::systems {
	RenderingSystem::RenderingSystem()
	{
	}

	RenderingSystem::~RenderingSystem()
	{
	}

	void RenderingSystem::Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{}

	void RenderingSystem::Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene)
	{
		spic::internal::Rendering::Clean();
		spic::internal::Rendering::UpdateCamera(&currentScene.Camera());
		auto filteredEntities = GetFilteredEntities(entities);
		const spic::TileMap* tileMap = currentScene.TileMap();
		if (tileMap != nullptr)
			tileMap->Render();
		for (const auto& entity : filteredEntities[0]) {
			spic::internal::Rendering::Draw(entity.get());
		}
		for (const auto& entity : filteredEntities[1]) {
			spic::internal::Rendering::Draw(entity.get());
		}
		if(Debug::DEBUG && Debug::COLLIDER_VISIBILITY)
			DrawBoxColliders(filteredEntities[0]);
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
			for (const auto& child : entity->GetChildren()) {
				if (spic::TypeHelper::SharedPtrIsOfType<UIObject>(child))
					uiEntities.emplace_back(child);
				else
					nonUIEntities.emplace_back(child);
			}
		}
		return { nonUIEntities, uiEntities };
	}


	void RenderingSystem::DrawBoxCollider(std::shared_ptr<spic::GameObject> entity)
	{
		for (const auto& child : entity->GetChildren()) {
			DrawBoxCollider(child);
		}
		if (entity->HasComponent<spic::BoxCollider>()) {
			std::shared_ptr<spic::BoxCollider> boxCollider = entity->GetComponent<spic::BoxCollider>();
			const auto& transform = entity->Transform();
			spic::Rect rect = spic::Rect(transform->position.x, transform->position.y, boxCollider->Width(), boxCollider->Height());
			spic::internal::Rendering::DrawRect(rect, transform->rotation, spic::Color::white());
		}
	}

	void RenderingSystem::DrawBoxColliders(std::vector<std::shared_ptr<spic::GameObject>>& entities)
	{
		for (const auto& entity : entities) {
			DrawBoxCollider(entity);
		}
	}
}