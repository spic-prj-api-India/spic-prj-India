#ifndef GAMEENGINEINFO_H_
#define GAMEENGINEINFO_H_

namespace spic {

    inline constexpr float FPS = 60.0f;

    inline int WINDOW_WIDTH = 1200;
    inline int WINDOW_HEIGHT = 800;

    inline float PIX2MET = 0.0023f;
    inline const float MET2PIX = 1.0f / PIX2MET;

    inline const float SCALED_WIDTH = WINDOW_WIDTH / MET2PIX;
    inline const float SCALED_HEIGHT = WINDOW_HEIGHT / MET2PIX;
}

#endif // GAMEENGINEINFO_H_