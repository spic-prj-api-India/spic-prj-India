#ifndef AUDIOFACADE_H_
#define AUDIOFACADE_H_

#include "AudioSource.hpp"

namespace spic::internal::audio {

    /**
     * @brief The AudioFacade
    */
    struct AudioFacade
    {
        /**
         * @brief If the sample does not exists it adds it to the Samples list
         * @param source The key value
         * @param looping If it should loop
        */
        static void PlaySample(AudioSource* source, const bool looping);

        /**
         * @brief stops all sounds of a sample
         * @param source The key
        */
        static void StopSample(AudioSource* source);

        /**
         * @brief Stops samples if they are playing
        */
        static void StopAllSamples();

        /**
         * @brief Adds a Sample to the sample list
         * @param source
        */
        static void AddSample(AudioSource* source);

        /**
         * @brief Removes a Sample from the sample list
         * @param source
        */
        static void RemoveSample(AudioSource* source);

        /**
         * @brief Change volume of a song with panning
         * @param source The key
         * @param left Value from 0 to 1
         * @param right Value from 0 to 1
        */
        static void ChangeVolume(AudioSource* source, const float left, const float right);

        /**
         * @brief Change the volume of a song
         * @param source The key
         * @param volume Value from 0 to 1
        */
        static void ChangeVolume(AudioSource* source, const float volume);

        /**
         * @brief Clears all buffer audio related stuff when a new scene is loaded
        */
        static void Reset();

        /**
         * @brief Creates an new AudioSystem
        */
        static void CreateAudio();

        /**
         * @brief Destorys the current audio system
        */
        static void DestroyAudio();
    };
}
#endif // AUDIOFACADE_H_