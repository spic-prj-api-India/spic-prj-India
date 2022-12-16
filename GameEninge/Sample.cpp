#include "Sample.hpp"
#include "Chunk.hpp"
#include "Debug.hpp"
#include <cmath>
#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include <SDL2/SDL_mixer.h>
#pragma warning( pop )

using namespace spic::internal::audio;

Sample* Sample::handlers[MAX_CHANNELS];

Sample::Sample(std::shared_ptr<Chunk> chunk, const bool looping)
    : chunk{ chunk }, looping{ looping }
{

}

void Sample::Play(const bool looping, float volume)
{
    if ((this->looping && looping) || looping)
    {
        this->Play(-1, volume);
    }
    else
    {
        mutex_.lock();
        const auto temp = Mix_PlayChannel(-1, chunk->GetChunk(), 0);
        channels.push_back(std::make_tuple(temp, false));
        handlers[temp] = this;
        mutex_.unlock();

        SetVolume(volume);
        running = true;
    }
}

void Sample::Play(const int times, float volume)
{
    mutex_.lock();

    const auto temp = Mix_PlayChannel(-1, chunk.get()->GetChunk(), times);
    channels.push_back(std::make_tuple(temp, true));
    handlers[temp] = this;
    
    mutex_.unlock();

    SetVolume(volume);

    running = true;
}

constexpr int ConvertVolume(const float volume, const float begin, const float end)
{
    auto lerpValue = std::lerp(begin, end, volume);
    return static_cast<int>(lerpValue < 0 ? lerpValue - 0.5 : lerpValue + 0.5);
}

void Sample::SetVolume(const float volume)
{
    Mix_Volume(std::get<0>(channels.back())
        , ConvertVolume(volume, VOLUME_BEGIN, VOLUME_END));
}

void Sample::SetVolume(const float left, const float right)
{   
    Mix_SetPanning(std::get<0>(channels.back())
        , ConvertVolume(left, VOLUME_BEGIN, 255)
        , ConvertVolume(right, VOLUME_BEGIN, 255));
}

void Sample::StopPlaying()
{
    std::vector<int> tempArray;

    mutex_.lock();
    for (const auto tuple : channels)
    {
        tempArray.push_back(std::get<0>(tuple));
    }
    running = false;
    mutex_.unlock();

    for (const auto& intValue : tempArray)
    {
        Mix_HaltChannel(intValue);
    }
}

void Sample::StopPlayingLast()
{
    mutex_.lock();
    Mix_HaltChannel(std::get<0>(channels.back()));

    static_cast<void>(channels.pop_back());

    if (channels.size() == 0)
        running = false;

    mutex_.unlock();
    
}

const bool Sample::IsRunning()
{
    return this->running;
}

void Sample::OnDone(const int chan)
{
    mutex_.lock();

    ptrdiff_t index = -1;
    for (auto it = channels.begin(); it != channels.end(); it++) {
       
        if (static_cast<int>(std::get<0>(*it)) == chan)
        {
            index = std::distance(channels.begin(), it);
            break;
        }
    }
    
    if (index != static_cast<ptrdiff_t>(-1))
        channels.erase(channels.begin(), channels.begin()+index);  

    if (channels.size() == 0)
        running = false;

    mutex_.unlock();
}

void Sample::CatchChannelDone(int chan)
{
    handlers[chan]->OnDone(chan);
}

Sample::~Sample()
{
    try
    {
        StopPlaying();
    }
    catch (const std::exception& ex)
    {
        spic::Debug::LogError(ex.what());
    }
}