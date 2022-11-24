#include <string>
#ifndef WINDOWINFO_H_
#define WINDOWINFO_H_

namespace spic::window {

    enum FULLSCREENTYPE
    {
        WINDOWED = 0,
        FULLSCREEN = 1,
        BORDERLESS = 2
    };

    /// @brief Values needed to start rendering
    struct WindowValues
    {
        /// @brief Name of the window
        std::string WindowName;

        /// @brief Width of the window
        int ScreenWidth;

        /// @brief Height of the window
        int ScreenHeight;

        /// @brief If the window is always on Top
        bool SetOnTop;

        /// @brief Which mode the window is
        FULLSCREENTYPE selector;
    };
}
#endif // AUDIOINFO_H_