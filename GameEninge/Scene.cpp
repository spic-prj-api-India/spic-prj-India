#include "Scene.hpp"

namespace spic
{
	Scene::Scene() : tileMapPath{ "" }, setting{ UpdateSetting::ALWAYS }
	{}

	std::vector<std::shared_ptr<GameObject>> Scene::Contents() const
	{
		return contents;
	}

	void Scene::AddContent(std::shared_ptr<GameObject> content)
	{
		contents.emplace_back(content);
	}

	std::string Scene::TileMapPath() const
	{
		return tileMapPath;
	}

	void Scene::TileMapPath(const std::string& newTileMapPath)
	{
		tileMapPath = newTileMapPath;
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