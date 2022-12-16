#ifndef SAMPLE_H_
#define SAMPLE_H_

#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <mutex>
#include "AudioInfo.hpp"


namespace spic::internal::audio::impl {
    class Chunk;

    /**
     * @brief The class that plays this sample
    */
    class Sample {
    public:
        
        /**
         * @brief Constructor of the sample class
         * @param chunk The chunk of music to play
         * @param looping If a song loops after playing
        */
        Sample(std::shared_ptr<Chunk> chunk, const bool looping);

        ~Sample(); // needed cause incomplete class
        Sample(const Sample& other) = default; // copy constructor
        Sample(Sample&& other) noexcept = default; // move constructor
        Sample& operator=(const Sample& other) = default; // copy assignment
        Sample& operator=(Sample&& other) noexcept = default;// move assignment
        
        /**
         * @brief Plays the song
         * @param looping Overwrites looping in the sample class
         * @param volume TBetween the value 0 and 1
        */
        void Play(const bool looping, const float volume);

        /**
         * @brief Overwriten method loops song x amount of time
         * @param times Times to loop
         * @param volume Between the value 0 and 1
        */
        void Play(const int times, const float volume);
        
        /**
         * @brief Set Volume of the song
         * @param volume Between the value 0 and 1
        */
        void SetVolume(const float volume);
        
        /**
         * @brief Sets panning of song
         * @param left Between the value 0 and 1
         * @param right Between the value 0 and 1
        */
        void SetVolume(const float left, const float right);

        /**
         * @brief Stops everything with playing
        */
        void StopPlaying();

        /**
         * @brief Stops only the last one with playing
        */
        void StopPlayingLast();
        
        /**
         * @brief Checks if this sample still has a song running
         * @return A bool if 
        */
        const bool IsRunning();
        
        /**
         * @brief After a song is done playing it calls this method
         * @param chan 
        */
        void OnDone(const int chan);
        
        /**
         * @brief Static method which triggers after a channel is done playing
         * @param chan 
        */
        static void CatchChannelDone(int chan);

    private:
        /**
         * @brief For use by CatchChannelDone
        */
        static Sample* handlers[MAX_CHANNELS];

        /**
         * @brief All playing channels and if they are looping
        */
        std::vector<std::tuple<int, bool>> channels;

        /**
         * @brief Thread safety
        */
        mutable std::mutex mutex_;

        /**
         * @brief 
        */
        std::shared_ptr<Chunk> chunk;

        /**
         * @brief If a song should loop by default
        */
        bool looping;

        /**
         * @brief If a Sample is currently running
        */
        bool running = false;
    };
}
#endif // SAMPLE_H_