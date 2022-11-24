#ifndef SCENE_H_
#define SCENE_H_

#include "GameObject.hpp"
#include "Camera.hpp"
#include <string>
#include "MapParser.hpp"

namespace spic {
    enum UpdateSetting { ALWAYS, CAMERA_VIEW };

    /**
     * @brief Class representing a scene which can be rendered by the Camera.
     */
    class Scene {
        public:
            Scene();
            Scene(std::unique_ptr<Camera> camera = std::make_unique<spic::Camera>(), UpdateSetting setting = UpdateSetting::ALWAYS);

            /**
             * @brief The scene's contents
             * @return The current contents
             * @spicapi
             */
            std::vector<std::shared_ptr<GameObject>> Contents() const;

            /**
             * @brief Add a Game object.
             * @details This function places a pointer to the game object in
             *          a suitable container.
             * @param content Reference to the game object.
             * @spicapi
             */
            void AddContent(std::shared_ptr<GameObject> content);


            /**
             * @brief Load tile map
             * @param newCollisionLayerIndex The desired collision layer index
             * @param newTileMapPath The desired tile map path
             * @spicapi
             */
            void LoadTileMap(const int newCollisionLayerIndex, const std::string& newTileMapPath);

            /**
            * @brief The scene's collision layer index
            * @return The current collision layer index
            * @spicapi
            */
            int CollisionLayerIndex() const;

            /**
             * @brief The scene's tile map
             * @return The current tile map
             * @spicapi
             */
            const MapParser& TileMap() const;

            /**
             * @brief The scene's camera
             * @return The current camera
             * @spicapi
             */
            const spic::Camera& Camera() const;

            /**
             * @brief Set camera
             * @param newCamera The desired camera
             * @spicapi
             */
            void Camera(std::unique_ptr<spic::Camera> newCamera);

            /**
             * @brief The scene's update setting
             * @return The current update setting
             * @spicapi
             */
            UpdateSetting UpdateSetting() const;

            /**
             * @brief Set update setting
             * @param newUpdateSetting The desired update setting
             * @spicapi
             */
            void UpdateSetting(spic::UpdateSetting newUpdateSetting);
    private:
        /**
        * @brief This property contains all the Game Object that are contained in this scene.
        * @spicapi
        */
        std::vector<std::shared_ptr<GameObject>> contents;
        int collisionLayerIndex;
        std::unique_ptr<MapParser> tileMap;
        std::unique_ptr<spic::Camera> camera;
        spic::UpdateSetting setting;
    };

}

#endif // SCENE_H_