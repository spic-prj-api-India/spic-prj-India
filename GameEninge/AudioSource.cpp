#include "AudioSource.hpp"
#include "AudioManager.hpp"
#include <cmath>

using namespace spic;
using namespace spic::internal::audio;

AudioSource::AudioSource(const std::string& audioClip, const bool playOnAwake, const bool loop, const float volume)
	: audioClip{ audioClip }, playOnAwake{ playOnAwake }, loop{ loop }, volume{ std::lerp(0.0f, 1.0f, volume) }
{
}

void AudioSource::Play(bool looping)
{
	AudioManager::GetInstance()->PlaySample(this, looping);
}

void AudioSource::Stop()
{
	AudioManager::GetInstance()->StopSample(this);
}

void AudioSource::ChangeVolume(float volume)
{
	AudioManager::GetInstance()->ChangeVolumn(this, volume);
}

void AudioSource::ChangeVolume(float left, float right)
{
	AudioManager::GetInstance()->ChangeVolumn(this, left, right);
}

const std::string AudioSource::GetAudioClip() const
{
	return this->audioClip;
}

const bool AudioSource::GetLoop() const
{
	return loop;
}

const float AudioSource::GetVolume() const
{
	return volume;
}