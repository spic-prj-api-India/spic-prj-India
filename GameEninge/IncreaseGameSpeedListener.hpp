#ifndef INCREASEGAMESPEEDLISTENER_H_
#define INCREASEGAMESPEEDLISTENER_H_

#include "IKeyListener.hpp"

/**
 * @brief Listene for a certain key to show the fps counter
*/
class IncreaseGameSpeedListener : public spic::IKeyListener
{
    void OnKeyPressed() override;
    void OnKeyReleased() override;

private:
    const INCREASE
};

#endif // INCREASEGAMESPEEDLISTENER_H_
