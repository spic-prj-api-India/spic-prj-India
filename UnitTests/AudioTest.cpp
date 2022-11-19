#include "gtest/gtest.h"
#include "AudioSource.hpp"

namespace internal
{
	TEST(AudioTest, no_exceptions)
	{
		try
		{
			auto temp = spic::AudioSource("", true, true, 1.0f);
			temp.Volume(0, 0);
			temp.Volume(0);
			temp.Stop();
			temp.Play(false);
		}
		catch (...) {
			FAIL();
		}
	}
}