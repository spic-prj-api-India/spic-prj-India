#include "ResetGameSpeedListener.hpp"
#include "Time.hpp"
#include "Settings.hpp"

using namespace spic::internal::input;

void ResetGameSpeedListener::OnKeyPressed()
{
	spic::Time::TimeScale(spic::settings::STANDARD_GAME_SPEED);
}

void ResetGameSpeedListener::OnKeyReleased()
{
}
