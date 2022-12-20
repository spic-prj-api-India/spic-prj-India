#ifndef INPUTIMPL_H_
#define INPUTIMPL_H_

#include <vector>
#include "Input.hpp"

namespace spic::internal::input::impl 
{

    /**
    * @brief Polls all input events, needs to be used to update input events
    * @spicapi
    */
    int Poll();

    /**
    * @brief Has quited? (Read Only)
    * @spicapi
    */
    bool Quit();

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
    bool GetKey(spic::input::KeyCode key);

    /**
     * @brief Returns true during the frame the user starts pressing down the key identified by keycode.
     * @spicapi
     */
    bool GetKeyDown(spic::input::KeyCode key);

    /**
     * @brief Returns true during the frame the user releases the key identified by keycode.
     * @spicapi
     */
    bool GetKeyUp(spic::input::KeyCode key);

    /**
     * @brief Returns whether the given mouse button is held down.
     * @spicapi
     */
    bool GetMouseButton(spic::input::MouseButton which);

    /**
     * @brief Returns true during the frame the user pressed the given mouse button.
     * @spicapi
     */
    bool GetMouseButtonDown(spic::input::MouseButton which);

    /**
     * @brief Returns true during the frame the user releases the given mouse button.
     * @spicapi
     */
    bool GetMouseButtonUp(spic::input::MouseButton which);
}

#endif // INPUTIMPL_H_