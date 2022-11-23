#ifndef SCENE_H_
#define SCENE_H_

#include "GameObject.hpp"
#include "Camera.hpp"
#include <string>

namespace spic {
    enum UpdateSetting { ALWAYS, CAMERA_VIEW };

    /**
     * @brief Class representing a scene which can be rendered by the Camera.
     */
    class Scene {
        public:
            Scene();

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
             * @brief The scene's tile map path
             * @return The current tile map path
             * @spicapi
             */
            std::string TileMapPath() const;

            /**
             * @brief Set tile map path
             * @param newTileMapPath The desired tile map path
             * @spicapi
             */
            void TileMapPath(const std::string& newTileMapPath);

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
        std::string tileMapPath;
        std::unique_ptr<spic::Camera> camera;
        spic::UpdateSetting setting;
    };

}

#endif // SCENE_H_