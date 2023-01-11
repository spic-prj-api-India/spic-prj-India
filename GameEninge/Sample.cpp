#include "Sample.hpp"
#include "Chunk.hpp"
#include "Debug.hpp"
#include <cmath>
#include "Defaults.hpp"
#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include <SDL2/SDL_mixer.h>
#pragma warning( pop )

using namespace spic::internal::audio::impl;

Sample* Sample::handlers[spic::settings::MAX_CHANNELS];

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

        const auto temp = Mix_PlayChannel(-1, chunk->GetChunk(), 0);

        if (temp == -1)
            return;

        channels.push_back(std::make_tuple(temp, false));
        handlers[temp] = this;

        SetVolume(volume);
        running = true;
    }
}

void Sample::Play(const int times, float volume)
{
    const auto temp = Mix_PlayChannel(-1, chunk.get()->GetChunk(), times);

    if (temp == -1)
        return;

    channels.push_back(std::make_tuple(temp, true));
    handlers[temp] = this;

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
        , ConvertVolume(volume, spic::internal::defaults::VOLUME_BEGIN, spic::internal::defaults::VOLUME_END));
}

void Sample::SetVolume(const float left, const float right)
{   
    Mix_SetPanning(std::get<0>(channels.back())
        , ConvertVolume(left, spic::internal::defaults::VOLUME_BEGIN, 255)
        , ConvertVolume(right, spic::internal::defaults::VOLUME_BEGIN, 255));
}

void Sample::StopPlaying()
{
    std::vector<int> tempArray;

    for (const auto tuple : channels)
    {
        tempArray.push_back(std::get<0>(tuple));
    }
    running = false;

    for (const auto& intValue : tempArray)
    {
        Mix_HaltChannel(intValue);
    }
}

void Sample::StopPlayingLast()
{
    Mix_HaltChannel(std::get<0>(channels.back()));

    static_cast<void>(channels.pop_back());

    if (channels.size() == 0)
        running = false;
}

const bool Sample::IsRunning()
{
    return this->running;
}

void Sample::OnDone(const int chan)
{
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
        spic::debug::LogError(ex.what());
    }
}