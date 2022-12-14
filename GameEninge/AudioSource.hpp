#ifndef AUDIOSOURCE_H_
#define AUDIOSOURCE_H_

#include "Component.hpp"
#include <string>

namespace spic {
    /**
     * @brief Component which can play audio.
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
             * @spicapi
             */
            void Stop();
            
            /**
            * @brief Call this method to change the playing volumen.
            * @param volume The value to change the current volumen.
            * @spicapi
            */
            void ChangeVolume(float volume);

            /**
            * @brief overloaded method to change the playing volumen.
            * @details Currently broken cause there is a bug in the used music library
            * @param volume The value to change the current volumen.
            * @spicapi
            */
            void ChangeVolume(float left, float right);

            /**
            * @brief the audiosource constructor 
            * @param audioClip Path to a locally stored audio file.
            * @param playOnAwake When true, the component will start playing automatically.
            * @param loop When true, the audio will play indefinitely.
            * @param Audio volume, between 0.0 and 1.0.
            * @spicapi
            */
            AudioSource(const std::string& audioClip, const bool playOnAwake, const bool loop, const float volume);

            const std::string AudioClip() const;
            void AudioClip(const std::string& audioClip);

            const bool PlayOnAwake() const;
            void PlayOnAwake(const bool playOnAwake);

            const bool Loop() const;
            void Loop(const bool loop);

            const float Volume() const;
            void Volume(const float volume);

        private:
            /**
             * @brief Path to a locally stored audio file.
             */
            std::string audioClip;

            /**
             * @brief When true, the component will start playing automatically.
             */
            bool playOnAwake;

            /**
             * @brief When true, the audio will play indefinitely.
             */
            bool loop;

            /**
             * @brief Audio volume, between 0.0 and 1.0.
             */
            float volume;
    };

}

#endif // AUDIOSOURCE_H_
