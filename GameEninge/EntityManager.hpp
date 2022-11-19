#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include <map>
#include <regex>
#include <memory>
#include <mutex>
#include <vector>
#include <iostream>
#include "ISystem.hpp"
#include "Scene.hpp"
#include "MapParser.hpp"

class EntityManager
{
private:
	static EntityManager* pinstance_;
	static std::mutex mutex_;

	std::vector<std::shared_ptr<spic::GameObject>> entities;
	std::vector <std::pair<int, spic::systems::ISystem>> systems;
	std::weak_ptr<spic::Scene> currentScene;
	std::unique_ptr<spic::MapParser> tileParser;
protected:
	EntityManager();
	~EntityManager();
public:
	EntityManager(EntityManager& other) = delete;
	EntityManager(EntityManager&& other) = delete;
	void operator=(const EntityManager& other) = delete;
	EntityManager& operator=(EntityManager&& other) = delete;
	static EntityManager* GetInstance();
};

#endif // ENTITYMANAGER_H_