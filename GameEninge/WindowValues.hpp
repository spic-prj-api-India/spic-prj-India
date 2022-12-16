#include <string>
#ifndef WINDOWINFO_H_
#define WINDOWINFO_H_

/**
 * @brief Values needed to start rendering
*/
namespace spic::window {
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
}
#endif // WINDOWINFO_H_