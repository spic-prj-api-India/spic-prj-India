#include <map>
#include <regex>
#include <memory>
#include <mutex>
#include <vector>
#include <iostream>
#include "EntityManager.hpp"
#include "ISystem.hpp"
#include "MapParser.hpp"
#include "InputSystem.hpp"
#include "PhysicsSystem.hpp"
#include "AISystem.hpp"
#include "RenderingSystem.hpp"
#include "AudioManager.hpp"
#include "NetworkingReceiveSystem.hpp"
#include "NetworkingSendSystem.hpp"
#include "InternalTime.hpp"
#include "Renderer.hpp"
#include "AudioFacade.hpp"
#include "GameEngine.hpp"
#include "PhysicsExtension1.hpp"
#include "Debug.hpp"

using namespace spic;
using namespace spic::internal;
using namespace spic::systems;

EntityManager* EntityManager::pinstance_{ nullptr };
std::mutex EntityManager::mutex_;

EntityManager::EntityManager() : CustomSystemDefaultPriority{ 1 }, scene{ nullptr }
{
	Init();
}

EntityManager::~EntityManager()
{
	try
	{
		spic::internal::audio::AudioFacade::DestroyAudio();
	}
	catch (std::exception& ex)
	{
		const std::string& message = ex.what();
		spic::debug::LogError("Audio destroy failed: " + message);
	}
}

EntityManager* EntityManager::GetInstance()
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (pinstance_ == nullptr)
		pinstance_ = new EntityManager();
	
	return pinstance_;
}

void EntityManager::Init()
{
	spic::internal::audio::AudioFacade::CreateAudio();
	std::unique_ptr<systems::InputSystem> inputSystem = std::make_unique<systems::InputSystem>();
	std::unique_ptr<systems::PhysicsSystem> physicsSystem = std::make_unique<systems::PhysicsSystem>();
	std::unique_ptr<systems::RenderingSystem> renderingSystem = std::make_unique<systems::RenderingSystem>();
	std::unique_ptr<systems::AISystem> aiSystem = std::make_unique<systems::AISystem>();
	std::unique_ptr<systems::NetworkingReceiveSystem> networkRecieve = std::make_unique<systems::NetworkingReceiveSystem>();
	std::unique_ptr<systems::NetworkingSendSystem> networkSend = std::make_unique<systems::NetworkingSendSystem>();
	AddInternalSystem(std::move(networkRecieve), 0);
	AddInternalSystem(std::move(inputSystem), 1);
	AddInternalSystem(std::move(physicsSystem), 2);
    AddInternalSystem(std::move(aiSystem), 3);
	AddInternalSystem(std::move(networkSend), 4);
	AddInternalSystem(std::move(renderingSystem), 5);
}

void EntityManager::Reset()
{
	entities.clear();
	systems.clear();
	scenes.clear();
	scene = nullptr;
}

std::vector<std::shared_ptr<spic::GameObject>> EntityManager::GetEntities() 
{
	return entities;
}

void EntityManager::AddEntity(std::shared_ptr<spic::GameObject> entity)
{
	if (entity->Name().empty())
		throw std::exception("Entity requires a name.");

	entities.emplace_back(std::move(entity));
}

void spic::internal::EntityManager::AddEntityAlsoToScene(const std::shared_ptr<spic::GameObject>& entity)
{
	AddEntity(entity);
	scene->AddContent(entity);
}

void EntityManager::RemoveEntity(const std::shared_ptr<spic::GameObject>& entity) 
{
	entities.erase(
		std::remove(entities.begin(), entities.end(), entity),
		entities.end());
}

void EntityManager::RegisterScene(const std::string& sceneName, std::function<spic::Scene* ()> scene)
{
	if (scenes.count(sceneName))
		throw std::exception("Scene with this name already exists.");

	scenes[sceneName] = scene;
}

std::shared_ptr<Scene> EntityManager::GetScene()
{
	return scene;
}

std::shared_ptr<Scene> EntityManager::GetScene(const std::string& sceneName)
{
	if (!scenes.count(sceneName))
		return nullptr;

	auto scene = std::shared_ptr<spic::Scene>(scenes[sceneName]());
	return std::move(scene);
}

void EntityManager::SetScene(const std::string& sceneName)
{
	if (!scenes.count(sceneName))
		throw std::exception("Scene does not exist.");

	auto scene = std::shared_ptr<spic::Scene>(scenes[sceneName]());
	SetScene(std::move(scene));
}

void EntityManager::SetScene(std::shared_ptr<Scene> newScene)
{
	if (&newScene->Camera() == nullptr)
		throw std::exception("No camera defined.");

	DestroyScene();
	scene = std::move(newScene);

	for (auto& entity : scene->Contents())
	{
		entities.push_back(entity);
	}

	for (const auto& systemsMap : systems)
		for (const auto& system : systemsMap.second)
			system->Start(entities, *scene);

	const TileMap* tileMap = scene->TileMap();
	if (tileMap != nullptr) {
		GameEngine* engine = GameEngine::GetInstance();
		for (const auto& weakExtension : engine->GetExtensions<spic::extensions::IPhysicsExtension>()) {
			if (const auto& physicsExtension = weakExtension.lock())
				physicsExtension->AddCollisionLayer(tileMap->GetCollisionLayer());
		}
	}

	spic::internal::audio::AudioFacade::Reset();
	spic::internal::Rendering::NewScene();


	for (auto& entity : entities)
	{
		if (entity->Active())
			entity->Active(true);
	}
	using namespace spic::internal::time;

	InternalTime::SetStartValues();
}

void EntityManager::DestroyScene(bool forceDelete)
{
	scene = nullptr;
	if (forceDelete)
		entities.clear();
	else
		entities.erase(std::remove_if(entities.begin(), entities.end()
			, [](const std::shared_ptr<spic::GameObject>& x){
				return !x->DontDestroyOnLoad(); 
			}), entities.end());
}

void EntityManager::AddSystem(std::unique_ptr<spic::systems::ISystem> system)
{
	if (!systems.count(CustomSystemDefaultPriority))
	{
		systems[CustomSystemDefaultPriority];
	}
	systems[CustomSystemDefaultPriority].emplace_back(std::move(system));
}

bool spic::internal::EntityManager::CheckIfNameExists(const std::string& name) const
{
	for (auto& entity : this->entities)
	{
		auto children = entity->GetChildren();
		if (spic::GameObject::CheckIfNameExists(children, name))
			return true;	
	}
	
	return false;
}

void EntityManager::AddInternalSystem(std::unique_ptr<spic::systems::ISystem> system, int priority)
{
	if (!systems.count(priority))
		systems[priority];

	systems[priority].emplace_back(std::move(system));
}

/**
 * @brief Keeps the entities alive for the duration of the frame.
 * @param systems The current active systems.
 * @param vectorCopy The current active enties.
 * @param scene The current scene.
*/
void UpdateSave(std::map<int, std::vector<std::unique_ptr<spic::systems::ISystem>>>& systems
	, std::vector<std::shared_ptr<spic::GameObject>>& vectorCopy
	, std::shared_ptr<spic::Scene> scene)
{
	for (const auto& systemsMap : systems)
		for (const auto& system : systemsMap.second)
			system->Update(vectorCopy, *scene);
}

void EntityManager::Update()
{
	std::vector<std::shared_ptr<spic::GameObject>> tempVect;

	std::copy(entities.begin(), entities.end(), std::back_inserter(tempVect));
	
	UpdateSave(this->systems,tempVect,scene);
}