// Use to remove SDL2 warnings from error list
#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include <SDL2/SDL_mixer.h>
#pragma warning( pop )
#include "AudioManager.hpp"
#include "Sample.hpp"
#include "Chunk.hpp"
#include "AudioSource.hpp"

using namespace spic::internal::audio::impl;

AudioManager::AudioManager()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        throw std::exception("Audiomanager could not be initialized");
    }

    // Amount of channels (Max amount of sounds playing at the same time)
    Mix_AllocateChannels(spic::settings::MAX_CHANNELS);
    Mix_ChannelFinished(Sample::CatchChannelDone);
}

AudioManager::~AudioManager()
{
    try
    {
        Mix_CloseAudio();
    }
    catch (...)
    {

    }
}

void AudioManager::AddChunk(const std::string& path)
{
    auto it = chunks.find(path);
    if (it == chunks.end())
        chunks.emplace(path, std::make_shared<Chunk>(path));
        
}

void AudioManager::ResetChunks()
{
    chunks.clear();
}

void AudioManager::TrimChunk(const std::string& path)
{
    const auto& temp = chunks[path];
    if (temp.use_count() == 1)
    {
        chunks.erase(path);
    }
}

void AudioManager::PlaySample(AudioSource* source, const bool looping)
{
    auto it = samples.find(source);
    
    if (it == samples.end())
    {
        std::string audioClip = source->AudioClip();
        AddChunk(audioClip);
        const auto& temp = chunks[audioClip];
        samples.emplace(source, std::make_unique<Sample>(temp, source->Loop()));
    }
    samples[source]->Play(looping, source->Volume());
}

void AudioManager::StopSample(AudioSource* source) const
{
    auto it = samples.find(source);
    if (it != samples.end())
    {
        it->second->StopPlaying();
    }
}

void AudioManager::StopAllSamples() const
{
    for (auto const& [key, val] : samples)
    {
        val->StopPlaying();
    }
}

void AudioManager::AddSample(AudioSource* source)
{
    auto it = samples.find(source);
    if (it != samples.end())
    {
        return;
    }
    else
    {
        AddChunk(source->AudioClip());
        samples.emplace(source, std::make_unique<Sample>(chunks[source->AudioClip()], source->Loop()));
    }
}

void AudioManager::RemoveSample(AudioSource* source)
{
    samples.erase(source);
    TrimChunk(source->AudioClip());
}

void AudioManager::ChangeVolume(AudioSource* source, const float left, const float right) const
{
    auto it = samples.find(source);
    if (it != samples.end())
    {
        it->second->SetVolume(left, right);
    }
}

void AudioManager::ChangeVolume(AudioSource* source, const float volume) const
{
    auto it = samples.find(source);
    if (it != samples.end())
    {
        it->second->SetVolume(volume);
    }
}

void AudioManager::Reset()
{
    for (auto const& [key, val] : samples)
    {
        val->StopPlaying();
    }

    chunks.clear();
    samples.clear();
}