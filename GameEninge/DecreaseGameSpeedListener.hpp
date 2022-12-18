#ifndef DECREASEGAMESPEEDLISTENER_H_
#define DECREASEGAMESPEEDLISTENER_H_

#include "IKeyListener.hpp"

namespace spic::internal::input
{
    /**
     * @brief Listene for a certain key to show the fps counter
    */
    class DecreaseGameSpeedListener : public spic::IKeyListener
    {
        void OnKeyPressed() override;
        void OnKeyReleased() override;
    };
}
#endif // DECREASEGAMESPEEDLISTENER_H_