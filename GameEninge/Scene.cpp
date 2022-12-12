#include "Scene.hpp"
#include "MapParser.hpp"
#include "EntityManager.hpp"
namespace spic
{
	Scene::Scene() : setting{ UpdateSetting::ALWAYS }
	{}

	Scene::Scene(std::unique_ptr<spic::Camera> newCamera, spic::UpdateSetting setting) :
		setting{ setting }
	{
		if (newCamera != nullptr)
			camera = std::move(newCamera);
	}

	std::vector<std::shared_ptr<GameObject>> Scene::Contents() const
	{
		return contents;
	}


	void Scene::AddContent(std::shared_ptr<GameObject> content)
	{
		for (auto& cont : contents)
		{
			if (cont->Name() == content->Name())
				throw "Name exsits already\n";
		}

		auto name = content->Name();
		if(spic::internal::EntityManager::GetInstance()->CheckIfNameExsitsInDontDestoryOnLoadObjects(name))
			throw "Name exsits already\n";

		this->contents.emplace_back(content);
	}

	void Scene::LoadTileMap(const std::string& newTileMapPath, const int newCollisionLayerIndex)
	{
		std::unique_ptr<spic::internal::MapParser> mapParser = std::make_unique<spic::internal::MapParser>();
		tileMap = mapParser->Parse(newTileMapPath, newCollisionLayerIndex);
	}

	const TileMap* Scene::TileMap() const
	{
		return tileMap.get();
	}

	spic::Camera& Scene::Camera() const
	{
		return *camera;
	}

	void Scene::Camera(std::unique_ptr<spic::Camera> newCamera)
	{
		camera = std::move(newCamera);
	}

	UpdateSetting Scene::UpdateSetting() const
	{
		return setting;
	}

	void Scene::UpdateSetting(spic::UpdateSetting newUpdateSetting)
	{
		setting = newUpdateSetting;
	}
}