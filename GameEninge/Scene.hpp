#ifndef SCENE_H_
#define SCENE_H_

#include "GameObject.hpp"
#include "Camera.hpp"
#include <string>

namespace spic {

    /**
     * @brief Class representing a scene which can be rendered by the Camera.
     */
    class Scene {
        public:
            Scene();

            enum UpdateSetting { ALWAYS, CAMERA_VIEW };
            std::string tileMapPath = "";
            std::string contentsPath = "";
            std::unique_ptr<Camera> camera;
            UpdateSetting setting;
            /**
             * @brief This property contains all the Game Object that are contained in this scene.
             * @spicapi
             */
            std::vector<std::shared_ptr<GameObject>> contents;
    };

}

#endif // SCENE_H_