#include "EntityManager.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "UIObject.hpp"
#include "ISystem.hpp"

using namespace spic::internal;

EntityManager* EntityManager::pinstance_{ nullptr };
std::mutex EntityManager::mutex_;

EntityManager::EntityManager()
{}

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
