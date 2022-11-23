#ifndef INPUTIMPL_H_
#define INPUTIMPL_H_

// Use to remove SDL2 warnings from error list
#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include <SDL2/SDL_events.h>
#pragma warning( pop )
#include <vector>
#include "Input.hpp"

namespace spic::internal::InputImpl {
    /**
    * @brief Converts KeyCode to SDL_KeyCode
    * @spicapi
    */
    std::vector<SDL_Keycode> ToSDLKeyCodes(spic::Input::KeyCode key);

    /**
    * @brief Polls all input events, needs to be used to update input events
    * @spicapi
    */
    int Poll();

    /**
     * @brief Is any key or mouse button currently held down? (Read Only)
     * @spicapi
     */
    bool AnyKey();

    /**
     * @brief Returns true the first frame the user hits any key or mouse button. (Read Only)
     * @spicapi
     */
    bool AnyKeyDown();

    /**
     * @brief The current mouse position in pixel coordinates. (Read Only)
     * @spicapi
     */
    spic::Point MousePosition();

    /**
     * @brief Returns the value of the virtual axis identified by axisName.
     * @spicapi
     */
    double GetAxis();

    /**
     * @brief Returns true while the user holds down the key identified by keycode.
     * @spicapi
     */
    bool GetKey(spic::Input::KeyCode key);

    /**
     * @brief Returns true during the frame the user starts pressing down the key identified by keycode.
     * @spicapi
     */
    bool GetKeyDown(spic::Input::KeyCode key);

    /**
     * @brief Returns true during the frame the user releases the key identified by keycode.
     * @spicapi
     */
    bool GetKeyUp(spic::Input::KeyCode key);

    /**
     * @brief Returns whether the given mouse button is held down.
     * @spicapi
     */
    bool GetMouseButton(spic::Input::MouseButton which);

    /**
     * @brief Returns true during the frame the user pressed the given mouse button.
     * @spicapi
     */
    bool GetMouseButtonDown(spic::Input::MouseButton which);

    /**
     * @brief Returns true during the frame the user releases the given mouse button.
     * @spicapi
     */
    bool GetMouseButtonUp(spic::Input::MouseButton which);
}

#endif // INPUTIMPL_H_