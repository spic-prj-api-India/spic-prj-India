#include "AudioSource.hpp"
#include "AudioFacade.hpp"
#include <cmath>

using namespace spic;
using namespace spic::internal::audio;

AudioSource::AudioSource(const std::string& audioClip, const bool playOnAwake, const bool loop, const float volume)
	: audioClip{ audioClip }, playOnAwake{ playOnAwake }, loop{ loop }, volume{ std::lerp(0.0f, 1.0f, volume) }
{
}

void AudioSource::Play(bool looping)
{
	AudioFacade::PlaySample(this, looping);
}

void AudioSource::Stop()
{
	AudioFacade::StopSample(this);
}

void AudioSource::ChangeVolume(float _volume)
{
	AudioFacade::ChangeVolume(this, _volume);
}

void AudioSource::ChangeVolume(float left, float right)
{
	AudioFacade::ChangeVolume(this, left, right);
}

const std::string AudioSource::AudioClip() const
{
	return this->audioClip;
}

void spic::AudioSource::AudioClip(const std::string& audioClip)
{
	this->audioClip = audioClip;
}

const bool AudioSource::PlayOnAwake() const {
	return playOnAwake;
}

void spic::AudioSource::PlayOnAwake(const bool playOnAwake)
{
	this->playOnAwake = playOnAwake;
}

const bool AudioSource::Loop() const
{
	return loop;
}

void spic::AudioSource::Loop(const bool loop)
{
	this->loop = loop;
}

const float AudioSource::Volume() const
{
	return volume;
}

void spic::AudioSource::Volume(const float volume)
{
	this->volume = std::lerp(0.0f, 1.0f, volume);
}
