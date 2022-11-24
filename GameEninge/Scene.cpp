#include "Scene.hpp"

namespace spic
{
	Scene::Scene()
	{}

	Scene::Scene(std::unique_ptr<spic::Camera> camera, spic::UpdateSetting setting) :
		camera{ std::move(camera) }, setting{ setting }
	{}

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
		tileMap = std::make_unique<MapParser>();
		tileMap->Parse(newTileMapPath);
	}

	const MapParser& Scene::TileMap() const
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