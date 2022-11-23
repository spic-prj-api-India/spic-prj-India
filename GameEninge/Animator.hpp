#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include "Component.hpp"
#include "Sprite.hpp"
#include <vector>
#include <memory>


namespace spic {

    /**
     * @brief A component which can play animated sequences of sprites.
     */
    class Animator : public Component {
        public:
            Animator(const int fps);

            /**
             * @brief Start playing the image sequence.
             * @param looping If true, will automatically start again when done.
             * @spicapi
             */
            void Play(bool looping);

            /**
             * @brief Stop playing the image sequence. Whatever sprite was displayed
             *        last will remain shown.
             * @spicapi
             */
            const void Freeze();
            const bool IsFozen() const;

            void Stop();

            void AddSprite(const std::shared_ptr<Sprite> sprite);
            const std::vector<std::shared_ptr<Sprite>> Sprites() const;

            const int Fps() const;
            const void Fps(const int fps);
            const bool Looping() const;
            const int Index() const;
            const void Index(const int index);
        private:
            /**
             * @brief frames per second (playing speed)
             * @spicapi
             */
            int fps;
            bool freeze;
            int index;
            bool looping;
            std::vector<std::shared_ptr<Sprite>> sprites;
    };

}

#endif // ANIMATOR_H_
