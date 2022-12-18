#include <string>
#ifndef SETTINGS_H_
#define SETTINGS_H_

/**
 * @brief Values needed to start rendering
*/
namespace spic::settings {

    /**
     * @brief Which type a window should be (currently only windowed supported)
    */
    enum class FULLSCREENTYPE
    {
        WINDOWED = 0,
        FULLSCREEN = 1,
        BORDERLESS = 2
    };

    /**
     * @brief Name of the window
    */
    inline std::string WINDOW_NAME = "Window name";

    /**
     * @brief Width of the window
    */
    inline int WINDOW_WIDTH = 1200;

    /**
     * @brief Height of the window
    */
    inline int WINDOW_HEIGHT = 800;

    /**
     * @brief If the window is always on Top
    */
    inline bool SET_ON_TOP = false;

    /**
     * @brief Which mode the window is
    */
    inline FULLSCREENTYPE SELECTOR = FULLSCREENTYPE::WINDOWED;

    /**
     * @brief gravity used in physics world
    */
    inline float GRAVITY = 9.81f;

    /**
     * @brief Max audio channels used
     *      To change this value you have to adjust the source code
    */
    inline constexpr int MAX_CHANNELS = 32;

    /*
     * @brief Enables or disables collider visibility.
    */
    inline bool COLLIDER_VISIBILITY = false;
}
#endif // SETTINGS_H_