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

            /// @brief Running is on by default
            /// @param fps amount of frames shown each second 
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

            /// @brief If the frame is frozen
            /// @return 
            const bool IsFrozen() const;

            /// @brief Stops the animator frow drawing frames
            void Stop();

            /// @brief Adds a sprite to the sprite list and resort the list
            /// @details the Orderlayer is amount of sprite frames so it is advised to start the first sprite 
            /// with orderlayer 1 and keep increasing from there.
            /// @param sprite 
            void AddSprite(const std::shared_ptr<Sprite> sprite);

            /// @brief Getter
            /// @return Sorted sprite list
            const std::vector<std::shared_ptr<Sprite>> Sprites() const;

            /// @brief Getter
            /// @return fps of animator
            const int Fps() const;

            /// @brief Setter
            /// @param fps of animator
            void Fps(const int fps);

            /// @brief getter
            /// @return if the animator is looping
            const bool Looping() const;

            /// @brief getter
            /// @return current frame index
            const int Index() const;

            /// @brief setter
            /// @return current frame index
            void Index(const int index);

            /// @brief dynamic increase of index not dependend on frame rate
            /// @details No functionality at this momen
            /// @param index 
            void IncreaseIndex(const int index);

        private:
            /**
             * @brief frames per second (playing speed)
             * @spicapi
             */
            int fps;

            /// @brief If this is true only the current frame will show
            bool freeze;

            /// @brief If this animator is running
            bool running;

            /// @brief The index of the current frame
            int index;

            /// @brief If the animation should loop
            bool looping;

            /// @brief sprites collection
            std::vector<std::shared_ptr<Sprite>> sprites;
    };
}

#endif // ANIMATOR_H_
