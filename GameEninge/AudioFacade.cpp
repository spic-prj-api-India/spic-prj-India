#include "AudioFacade.hpp"
#include "Audiomanager.hpp"

using namespace spic::internal::audio::impl;

/**
 * @brief The current audioManager has an exception if it is placed in an rai class.
 *		And since you don't want it on the stack the create and destory are the best options. 
*/
static AudioManager* manager; 

void spic::internal::audio::AudioFacade::PlaySample(AudioSource* source, const bool looping)
{
	if (manager == nullptr)
		spic::internal::audio::AudioFacade::CreateAudio();

	manager->PlaySample(source, looping);
}

void spic::internal::audio::AudioFacade::StopSample(AudioSource* source)
{
	if (manager == nullptr)
		spic::internal::audio::AudioFacade::CreateAudio();

	manager->StopSample(source);
}

void spic::internal::audio::AudioFacade::StopAllSamples()
{
	if (manager == nullptr)
		spic::internal::audio::AudioFacade::CreateAudio();

	manager->StopAllSamples();
}

void spic::internal::audio::AudioFacade::AddSample(AudioSource* source)
{
	if (manager == nullptr)
		spic::internal::audio::AudioFacade::CreateAudio();

	manager->AddSample(source);
}

void spic::internal::audio::AudioFacade::RemoveSample(AudioSource* source)
{
	if (manager == nullptr)
		spic::internal::audio::AudioFacade::CreateAudio();

	manager->RemoveSample(source);
}

void spic::internal::audio::AudioFacade::ChangeVolume(AudioSource* source, const float left, const float right)
{
	if (manager == nullptr)
		spic::internal::audio::AudioFacade::CreateAudio();

	manager->ChangeVolume(source,left,right);
}

void spic::internal::audio::AudioFacade::ChangeVolume(AudioSource* source, const float volume)
{
	if (manager == nullptr)
		spic::internal::audio::AudioFacade::CreateAudio();

	manager->ChangeVolume(source, volume);
}

void spic::internal::audio::AudioFacade::Reset()
{
	if (manager == nullptr)
		spic::internal::audio::AudioFacade::CreateAudio();
	manager->Reset();
}

void spic::internal::audio::AudioFacade::CreateAudio()
{
	delete manager;
	manager = new AudioManager();
}

void spic::internal::audio::AudioFacade::DestroyAudio()
{
	delete manager;
}
