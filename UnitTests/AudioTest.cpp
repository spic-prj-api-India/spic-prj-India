#include "pch.h"
#include "AudioSource.hpp"

namespace internal
{
	TEST(AudioTest, no_exceptions)
	{
		try
		{
			auto temp = spic::AudioSource("", true, true, 1.0f);
			temp.ChangeVolume(0, 0);
			temp.ChangeVolume(0);
			temp.Stop();
			temp.Play(false);
		}
		catch (...) {
			FAIL();
		}

	}
}