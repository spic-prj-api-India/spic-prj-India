#ifndef FPSLISTENER_H_
#define FPSLISTENER_H_

#include "IKeyListener.hpp"

namespace spic::internal::input
{
    /**
    * @brief Listens for a certain key to show the fps counter
    */
    class FPSListener : public spic::IKeyListener
    {
        void OnKeyPressed() override;
        void OnKeyReleased() override;

    public:
        static bool renderFps;
    };
}


#endif // FPSLISTENER_H_