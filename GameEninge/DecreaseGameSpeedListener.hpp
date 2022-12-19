#ifndef DECREASEGAMESPEEDLISTENER_H_
#define DECREASEGAMESPEEDLISTENER_H_

#include "IKeyListener.hpp"

/**
 * @brief Contains internal button/mouse listener
*/
namespace spic::internal::input
{
    /**
     * @brief Listens for a certain key to show the fps counter
    */
    class DecreaseGameSpeedListener : public spic::IKeyListener
    {
        void OnKeyPressed() override;
        void OnKeyReleased() override;
    };
}
#endif // DECREASEGAMESPEEDLISTENER_H_