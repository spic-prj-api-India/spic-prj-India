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
             * @spicapi
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
             * @spicapi
             */
            const void Freeze();
            
            /**
             * @brief Getter if the animator is frozen
             * @spicapi
             * @return 
            */
            const bool IsFrozen() const;

            /**
             * @brief 
             * @param width Width of an individual sprite in a vertical spriteSheet 
             * @param height Heigth of an individual sprite in a vertical spriteSheet 
             * @param yOffsett Starting place on the y axis
             * @param xOffsett Starting place on the x axis
             * @spicapi
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
             * @spicapi
            */
            void Stop();
            
            /**
             * @brief Adds a sprite to the sprite list and resort the list
             *      The last orderlayer is amount of sprite frames so it is advised to start the first sprite 
             *      with orderlayer 1 and keep increasing from there.
             * @param sprite 
            */
            void AddSprite(const std::shared_ptr<Sprite> sprite);
            
            /**
             * @brief Getter
             * @return sprite list
             * @spicapi
            */
            const std::vector<std::shared_ptr<Sprite>> Sprites() const;
            
            /**
             * @brief Getter
             * @return Animation speed
             * @spicapi
            */
            const int Fps() const;
            
            /**
             * @brief Setter
             * @param fps Animation speed
             * @spicapi
            */
            void Fps(const int fps);
            
            /**
             * @brief getter
             * @return if the animator is looping
             * @spicapi
            */
            const bool Looping() const;
            
            /**
             * @brief getter
             * @return current frame index
             * @spicapi
            */
            const int Index() const;
            
            /**
             * @brief setter
             * @param index 
             * @spicapi
            */
            void Index(const int index);

            /**
             * @brief increase index by 1 (includes wrapping)
             * @spicapi
            */
            void IncreaseIndex();

            /**
             * @brief If the animator is playing
             * @spicapi
            */
            bool IsRunning() const;

            /**
             * @brief Lastupdate in miliseconds
             * @return 
             * @spicapi
            */
            uint64_t LastUpdate() const;

            /**
             * @brief Setter for last update
             * @param lastUpdate 
             * @spicapi
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
             * @spicapi
            */
            bool freeze;

            /**
             * @brief If this animator is running
             * @spicapi
            */
            bool running;

            /**
             * @brief The index of the current frame
             * @spicapi
            */
            int index;

            /**
             * @brief If the animation should loop
             * @spicapi
            */
            bool looping;

            /**
             * @brief sprites collection
             * @spicapi
            */
            std::vector<std::shared_ptr<Sprite>> sprites;

            /**
             * @brief Last update
             * @spicapi
            */
            uint64_t lastUpdate = 0;
    };
}

#endif // ANIMATOR_H_