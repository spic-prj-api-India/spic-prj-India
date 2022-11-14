#include "AudioManager.hpp"
#pragma warning(push, 0) // needed to resolve warnings
#include <SDL2/SDL_mixer.h>
#pragma warning(pop)
#include "Sample.hpp"
#include "Chunk.hpp"
#include "AudioSource.hpp"

using namespace spic::internal::audio;

AudioManager* AudioManager::pinstance_{ nullptr };
std::mutex AudioManager::mutex_;

AudioManager::AudioManager()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        throw std::exception("Audiomanager could not be initialized");
    }

    // Amount of channels (Max amount of sounds playing at the same time)
    Mix_AllocateChannels(MAX_CHANNELS);
    Mix_ChannelFinished(Sample::CatchChannelDone);
}


AudioManager::~AudioManager()
{
    Mix_CloseAudio();
}

AudioManager* AudioManager::GetInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new AudioManager();
    }
    return pinstance_;
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
    auto temp = chunks[path];
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
        std::string audioClip = source->GetAudioClip();
        AddChunk(audioClip);
        auto temp = chunks[audioClip];
        samples.emplace(source, std::make_unique<Sample>(temp, source->GetLoop()));
    }
    samples[source]->Play(looping, source->GetVolume());
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
        AddChunk(source->GetAudioClip());
        samples.emplace(source, std::make_unique<Sample>(chunks[source->GetAudioClip()], source->GetLoop()));
    }
}

void AudioManager::RemoveSample(AudioSource* source)
{
    samples.erase(source);
    TrimChunk(source->GetAudioClip());
}


void AudioManager::ChangeVolumn(AudioSource* source, float left, float right) const
{
    auto it = samples.find(source);
    if (it != samples.end())
    {
        it->second->SetVolume(left, right);
    }
}

void AudioManager::ChangeVolumn(AudioSource* source, float volume) const
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