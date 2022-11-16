#include "EntityManager.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "UIObject.hpp"

namespace spic::internal
{

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

	void EntityManager::SetScene(std::weak_ptr<Scene> scene)
	{
		auto lock = scene.lock();

		if (lock)
		{
			for (auto& entity : lock->contents) 
			{
				entities.push_back(entity);
			}
		}		
	}

	void EntityManager::DestroyScene(bool forceDelete)
	{

	}

	void EntityManager::AddSystem(ISystem* system)
	{}

	void EntityManager::RemoveSystem(ISystem* system)
	{}

	void EntityManager::Update(int deltaTime)
	{}

	void EntityManager::Render()
	{}
}