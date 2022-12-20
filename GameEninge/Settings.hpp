#include <string>
#ifndef SETTINGS_H_
#define SETTINGS_H_
#include "Input.hpp"
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
    * @brief Enables or disables collider visibility. Default false.
    */
    inline bool COLLIDER_VISIBILITY = false;

    /*
    * @brief Enables or disables feelers visibility for wall avoidance. Default false.
    */
    inline bool WALL_AVOIDANCE_FEELERS_VISIBILITY = false;
    
    /**
     * @brief Standard game speed cannot be lower then 0 and higer then 2;
    */
    inline double STANDARD_GAME_SPEED = 1.0;

    /**
    * @brief The speed increase and decrease rate.
        Cannot be lower then 0 and higer then 2;
    */
    inline double GAME_SPEED_INCREASE_AND_DECREASE_RATE = 0.1;

    /**
     * @brief The button bound to speeding up the game
    */
    inline spic::input::KeyCode INCREASE_SPEED = spic::input::KeyCode::PAGE_UP;

    /**
     * @brief The button bound to decreasing the speed of the game
    */
    inline spic::input::KeyCode DECREASE_SPEED = spic::input::KeyCode::PAGE_DOWN;

    /**
     * @brief The button bound to reseting the game speed
    */
    inline spic::input::KeyCode RESET_SPEED = spic::input::KeyCode::HOME;

    /**
     * @brief Button bound to show/not show the fps counter
    */
    inline spic::input::KeyCode BOUND_BUTTON_FPS_COUNTER = spic::input::KeyCode::F1;

    /**
     * @brief Which mouse button is used for clicking on ui buttons
    */
    inline spic::input::MouseButton MOUSEBUTTON_BOUND_TO_BUTTONS = spic::input::MouseButton::LEFT;

    /**
     * @brief If false it clears fonts and textures after each frame but the animations speed of the animator does not work correctly.
     *      If true it keeps them loaded for the duration of the scene.
    */
    inline bool KEEP_TEXTURES_AND_FONTS_LOADED = true;
}
#endif // SETTINGS_H_