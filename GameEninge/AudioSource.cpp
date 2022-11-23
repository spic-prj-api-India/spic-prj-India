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

void AudioSource::ChangeVolume(float _volume)
{
	volume = _volume;
	AudioManager::GetInstance()->ChangeVolume(this, _volume);
}

void AudioSource::ChangeVolume(float left, float right)
{
	AudioManager::GetInstance()->ChangeVolume(this, left, right);
}

const std::string AudioSource::AudioClip() const
{
	return this->audioClip;
}

const bool AudioSource::PlayOnAwake() const {
	return playOnAwake;
}

const bool AudioSource::Loop() const
{
	return loop;
}

const float AudioSource::Volume() const
{
	return volume;
}