#include "EntityManager.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "UIObject.hpp"

EntityManager* EntityManager::pinstance_{ nullptr };
std::mutex EntityManager::mutex_;

std::vector<std::shared_ptr<spic::GameObject>> entities;

EntityManager::~EntityManager()
{}

EntityManager* EntityManager::GetInstance()
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (pinstance_ == nullptr)
	{
		pinstance_ = new EntityManager();
	}
	return pinstance_;
}

void EntityManager::SetScene(spic::Scene* scene)
{
	for (auto& entity : scene->contents) {
		entities.push_back(entity);
	}
}

void EntityManager::DestroyScene(bool forceDelete)
{}

void EntityManager::AddSystem(ISystem* system)
{}

void EntityManager::RemoveSystem(ISystem* system)
{}

void EntityManager::Update(int deltaTime)
{}

void EntityManager::Render()
{}