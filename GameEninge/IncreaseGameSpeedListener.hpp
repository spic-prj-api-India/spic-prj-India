#ifndef INCREASEGAMESPEEDLISTENER_H_
#define INCREASEGAMESPEEDLISTENER_H_

#include "IKeyListener.hpp"

/**
 * @brief Contains internal button/mouse listeners and the input implementation
*/
namespace spic::internal::input
{
    /**
    * @brief Listens for a certain key to show the fps counter
    */
    class IncreaseGameSpeedListener : public spic::IKeyListener
    {
        void OnKeyPressed() override;
        void OnKeyReleased() override;
    };
}

#endif // INCREASEGAMESPEEDLISTENER_H_
