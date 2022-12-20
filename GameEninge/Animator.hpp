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
            /**
             * @brief Running is on by default
             * @param fps Playing speed (amount of frames show each second)
             * @sharedapi
            */
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
             * @sharedapi
             */
            const void Freeze();
            
            /**
             * @brief Getter 
             * @return If the animator is frozen
             * @sharedapi
            */
            const bool IsFrozen() const;

            /**
             * @brief If the sprite animation on the sprite sheet is horizontal,
             *      it does the sprite settings automaticly. 
             * @param width Width of an individual sprite in a vertical spriteSheet 
             * @param height Heigth of an individual sprite in a vertical spriteSheet 
             * @param yOffsett Starting place on the y axis
             * @param xOffsett Starting place on the x axis
             * @sharedapi
            */
            void InitHorizontalSpriteSheet(
                const std::string& spriteSheet
                , const int frames
                , const int width
                , const int height
                , const int yOffsett = 0
                , const int xOffsett = 0);

            /**
             * @brief Stops the animator frow drawing frames
             * @sharedapi
            */
            void Stop();
            
            /**
             * @brief Adds a sprite to the sprite list and resort the list
             *      The last orderlayer is amount of sprite frames so it is advised to start the first sprite 
             *      with orderlayer 1 and keep increasing from there.
             * @param sprite 
             * @sharedapi
            */
            void AddSprite(const std::shared_ptr<Sprite> sprite);
            
            /**
             * @brief Getter
             * @return The current sprite list
             * @sharedapi
            */
            const std::vector<std::shared_ptr<Sprite>> Sprites() const;
            
            /**
             * @brief Getter
             * @return Animation speed
             * @sharedapi
            */
            const int Fps() const;
            
            /**
             * @brief Setter
             * @param fps Animation speed
             * @sharedapi
            */
            void Fps(const int fps);
            
            /**
             * @brief Getter
             * @return If the animator is looping
             * @sharedapi
            */
            const bool Looping() const;

            /**
             * @brief Setter
             * @param looping If the animator should loop
             * @sharedapi
             */
            void Looping(const bool looping);
            
            /**
             * @brief getter
             * @return current frame index
             * @sharedapi
            */
            const int Index() const;
            
            /**
             * @brief setter
             * @param index 
             * @sharedapi
            */
            void Index(const int index);

            /**
             * @brief increase index by 1 (includes wrapping)
             * @sharedapi
            */
            void IncreaseIndex();

            /**
             * @brief If the animator is playing
             * @sharedapi
            */
            bool IsRunning() const;

            /**
             * @brief Getter
             * @return Lastupdate in miliseconds
             * @sharedapi
            */
            uint64_t LastUpdate() const;

            /**
             * @brief Setter 
             * @param lastUpdate 
             * @sharedapi
            */
            void LastUpdate(const uint64_t lastUpdate);
        private:
            /**
             * @brief frames per second (playing speed)
             * @spicapi
             */
            int fps;

            /**
             * @brief If this is true only the current frame will show
             * @sharedapi
            */
            bool freeze;

            /**
             * @brief If this animator is running
             * @sharedapi
            */
            bool running;

            /**
             * @brief The index of the current frame
             * @sharedapi
            */
            int index;

            /**
             * @brief If the animation should loop
             * @sharedapi
            */
            bool looping;

            /**
             * @brief sprites collection
             * @sharedapi
            */
            std::vector<std::shared_ptr<Sprite>> sprites;

            /**
             * @brief Last update
             * @sharedapi
            */
            uint64_t lastUpdate = 0;
    };
}

#endif // ANIMATOR_H_