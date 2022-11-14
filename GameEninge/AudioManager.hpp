#ifndef AUDIOMANAGER_H_
#define AUDIOMANAGER_H_

#include <mutex>
#include <string>
#include <memory>
#include <map>
#include "AudioSource.hpp"
#include "AudioInfo.hpp"


/// @brief The internal audio namespace wich contains all audio related content
namespace spic::internal::audio {
    class Sample;
    class Chunk;

    /// @brief Manages the audio samples and loaded songs(chunks). Is an singelton
    class AudioManager
    {   
        /**
        * The Singleton's constructor/destructor should always be private to
        * prevent direct construction/desctruction calls with the `new`/`delete`
        * operator.
        */
    private:
        static AudioManager* pinstance_;
        static std::mutex mutex_;

        /// @brief Holds all samples where the key is an audiosource
        std::map<AudioSource*, std::unique_ptr<Sample>> samples;

        /// @brief Holds all loaded audio chunks
        std::map<std::string, std::shared_ptr<Chunk>> chunks;

        /// @brief Mutex for making the private instance of this class thread safe
        std::mutex mutex_samples;

        /// @brief Adds a loaded chunk object to the chunks mpap
        /// @param path The path to the song(mp3, flac, of wav)
        void AddChunk(const std::string& path);

        /// @brief Checks and removes chunk if there is only 1 loaded in the chunks map 
        /// @param path 
        void TrimChunk(const std::string& path);

        /// @brief Clears the chunks map
        void ResetChunks();

    protected:
        AudioManager();
        ~AudioManager();
    public:
        /**
            * Singletons should not be cloneable or assignable.
            */
        AudioManager(const AudioManager& other) = delete; // copy constructor
        AudioManager(AudioManager&& other) noexcept = delete; // move constructor
        AudioManager& operator=(const AudioManager& other) = delete; // copy assignment
        AudioManager& operator=(AudioManager&& other) noexcept = delete;// move assignment


        /**
            * This is the static method that controls the access to the singleton
            * instance. On the first run, it creates a singleton object and places it
            * into the static field. On subsequent runs, it returns the client existing
            * object stored in the static field.
            */

        static AudioManager* GetInstance();

        /**
            * Finally, any singleton should define some business logic, which can be
            * executed on its instance.
            */

        /// @brief If the sample does not exists it adds it to the Samples list
        /// @param source The key value
        /// @param looping If it should loop
        void PlaySample(AudioSource* source, const bool looping);

        /// @brief stops all sounds of a sample
        /// @param source The key
        void StopSample(AudioSource* source) const;

        /// @brief Stops samples if they are playing
        void StopAllSamples() const;

        /// @brief Adds a Sample to the sample list
        /// @param source 
        void AddSample(AudioSource* source);

        /// @brief Removes a Sample from the sample list
        /// @param source 
        void RemoveSample(AudioSource* source);

        /// @brief Change volume of a song with panning
        /// @param source The key
        /// @param left Value from 0 to 1
        /// @param right Value from 0 to 1
        void ChangeVolumn(AudioSource* source, float left, float right) const;

        /// @brief Change the volume of a song
        /// @param source The key
        /// @param volume Value from 0 to 1
        void ChangeVolumn(AudioSource* source, float volume) const;

        /// @brief Clears the vector list samples and chunks
        void Reset();
    };
}
#endif // AUDIOMANAGER_H_