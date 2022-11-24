#include "Scene.hpp"
#include "MapParser.hpp"

namespace spic
{
	Scene::Scene() : setting{ UpdateSetting::ALWAYS }, collisionLayerIndex{ -1 }
	{}

	Scene::Scene(std::unique_ptr<spic::Camera> newCamera, spic::UpdateSetting setting) :
		setting{ setting }
	{
		if (newCamera != nullptr)
			camera = std::move(newCamera);
		camera = std::make_unique<spic::Camera>();
	}

	std::vector<std::shared_ptr<GameObject>> Scene::Contents() const
	{
		return contents;
	}

	void Scene::AddContent(std::shared_ptr<GameObject> content)
	{
		contents.emplace_back(content);
	}

	int Scene::CollisionLayerIndex() const
	{
		return collisionLayerIndex;
	}

	void Scene::LoadTileMap(const int newCollisionLayerIndex, const std::string& newTileMapPath)
	{
		collisionLayerIndex = newCollisionLayerIndex;
		std::unique_ptr<spic::internal::MapParser> mapParser = std::make_unique<spic::internal::MapParser>();
		tileMap = mapParser->Parse(newTileMapPath);
	}

	spic::internal::TileMap& Scene::TileMap() const
	{
		return *tileMap;
	}

	const spic::Camera& Scene::Camera() const
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