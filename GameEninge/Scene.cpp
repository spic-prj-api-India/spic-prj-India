#include "Scene.hpp"
#include "MapParser.hpp"
#include "EntityManager.hpp"
#include "Debug.hpp"

namespace spic
{
	Scene::Scene() : setting{ UpdateSetting::ALWAYS }
	{
	}

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
		try
		{
			if (GameObject::CheckIfNameExists(content->GetChildren(), content->Name()))
				throw std::runtime_error("Name of current gameobject exists already");

			if (spic::internal::EntityManager::GetInstance()->CheckIfNameExists(content->Name()))
				throw std::runtime_error("Name of current gameobject exists already");;

			this->contents.emplace_back(std::move(content));
		}
		catch (std::exception& ex)
		{
			debug::LogError(ex.what());
		}
	}

	void Scene::LoadTileMap(const std::string& newTileMapPath, const int newCollisionLayerIndex)
	{
		std::unique_ptr<spic::internal::MapParser> mapParser = std::make_unique<spic::internal::MapParser>(newCollisionLayerIndex);
		tileMap = mapParser->Parse(newTileMapPath);
	}

	const spic::tiled::TileMap* Scene::TileMap() const
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