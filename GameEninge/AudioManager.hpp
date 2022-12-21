#ifndef AUDIOMANAGER_H_
#define AUDIOMANAGER_H_

#include <mutex>
#include <string>
#include <memory>
#include <map>
#include "AudioSource.hpp"
#include "Settings.hpp"
#include "Sample.hpp"
#include "Chunk.hpp"

/**
 * @brief The internal audio namespace which contains all the audio implementation details
*/
namespace spic::internal::audio::impl {

    /**
     * @brief Manages the audio samples and loaded songs(chunks).
    */
    class AudioManager
    {   
    public:
        /**
         * @brief Sets up the audio devices
        */
        AudioManager();
        ~AudioManager();
    

        AudioManager(const AudioManager& other) = delete; // copy constructor
        AudioManager(AudioManager&& other) noexcept = delete; // move constructor
        AudioManager& operator=(const AudioManager& other) = default; // copy assignment
        AudioManager& operator=(AudioManager&& other) noexcept = default;// move assignment

        
        /**
         * @brief If the sample does not exists it adds it to the Samples list
         * @param source The key value
         * @param looping If it should loop
        */
        void PlaySample(AudioSource* source, const bool looping);

        /**
         * @brief stops all sounds of a sample
         * @param source The key
        */
        void StopSample(AudioSource* source) const;

        /**
         * @brief Stops samples if they are playing
        */
        void StopAllSamples() const;
        
        /**
         * @brief Adds a Sample to the sample list
         * @param source 
        */
        void AddSample(AudioSource* source);
        
        /**
         * @brief Removes a Sample from the sample list
         * @param source 
        */
        void RemoveSample(AudioSource* source);
        
        /**
         * @brief Change volume of a song with panning
         * @param source The key
         * @param left Value from 0 to 1
         * @param right Value from 0 to 1
        */
        void ChangeVolume(AudioSource* source, const float left, const float right) const;

        /**
         * @brief Change the volume of a song
         * @param source The key
         * @param volume Value from 0 to 1
        */
        void ChangeVolume(AudioSource* source, const float volume) const;

        /**
         * @brief Clears the vector list samples and chunks
        */
        void Reset();
    private:
        /**
         * @brief Adds a loaded chunk object to the chunks mpap
         * @param path The path to the song(mp3, flac, of wav)
        */
        void AddChunk(const std::string& path);

        /**
         * @brief Checks and removes chunk if there is only 1 loaded in the chunks map
         * @param path
        */
        void TrimChunk(const std::string& path);

        /**
         * @brief Clears the chunks map
        */
        void ResetChunks();
    private:

        /**
         * @brief Holds all samples where the key is an audiosource
        */
        std::map<AudioSource*, std::unique_ptr<Sample>> samples;

        /**
         * @brief Holds all loaded audio chunks
        */
        std::map<std::string, std::shared_ptr<Chunk>> chunks;
    };
}
#endif // AUDIOMANAGER_H_