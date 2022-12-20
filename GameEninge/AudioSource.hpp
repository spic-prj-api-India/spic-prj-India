#ifndef AUDIOSOURCE_H_
#define AUDIOSOURCE_H_

#include "Component.hpp"
#include <string>

namespace spic 
{
    /**
     * @brief Component which plays audio.
     */
    class AudioSource : public Component {
        public:
            /**
             * @brief Call this method to start playing audio.
             * @param looping Automatically start over when done.
             * @spicapi
             */
            void Play(bool looping);

            /**
             * @brief Call this method to stop playing audio.
             * @sharedapi
             */
            void Stop();
            
            /**
            * @brief Call this method to change the playing volumen.
            * @param volume The value to change the current volumen.
            * @sharedapi
            */
            void ChangeVolume(float volume);

            /**
            * @brief Overloaded method to change the playing volumen.
            * @details Currently broken cause there is a bug in the used music library
            * @param volume The value to change the current volumen.
            * @sharedapi
            */
            void ChangeVolume(float left, float right);

            /**
            * @brief The audiosource constructor 
            * @param audioClip Path to a locally stored audio file.
            * @param playOnAwake When true, the component will start playing automatically.
            * @param loop When true, the audio will play indefinitely.
            * @param audio The volume [0.0 <=> 1.0].
            * @sharedapi
            */
            AudioSource(const std::string& audioClip, const bool playOnAwake, const bool loop, const float volume);

            /**
             * @brief Getter
             * @return The location where the audio clip is
             * @sharedapi
            */
            const std::string AudioClip() const;

            /**
             * @brief Setter
             * @param audioClip Sets an new Audio location 
             * @sharedapi
            */
            void AudioClip(const std::string& audioClip);

            /**
             * @brief Getter
             * @return If this component should play when the GameObject is active
             * @sharedapi
            */
            const bool PlayOnAwake() const;

            /**
             * @brief Setter
             * @param playOnAwake If this component should play when the GameObject is active
             * @sharedapi
            */
            void PlayOnAwake(const bool playOnAwake);

            /**
             * @brief Getter 
             * @return If the audiosource should loop by default
             * @sharedapi
            */
            const bool Loop() const;

            /**
             * @brief Setter
             * @param loop If the audiosource should loop by default
             * @sharedapi
            */
            void Loop(const bool loop);

            /**
             * @brief Getter
             * @return The volume [0 <=> 1.0]
             * @sharedapi
            */
            const float Volume() const;

            /**
             * @brief setter
             * @param volume The volume [0 <=> 1.0]
             * @sharedapi
            */
            void Volume(const float volume);

        private:
            /**
             * @brief Path to a locally stored audio file.
             * @spicapi
             * @sharedapi
             */
            std::string audioClip;

            /**
             * @brief When true, the component will start playing automatically.
             * @spicapi
             */
            bool playOnAwake;

            /**
             * @brief When true, the audio will play indefinitely.
             * @spicapi
             */
            bool loop;

            /**
             * @brief Audio volume, between 0.0 and 1.0.
             * @sharedapi
             */
            float volume;
    };

}

#endif // AUDIOSOURCE_H_
