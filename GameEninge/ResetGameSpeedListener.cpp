#include "ResetGameSpeedListener.hpp"
#include "Time.hpp"
#include "Settings.hpp"

void ResetGameSpeedListener::OnKeyPressed()
{
	spic::Time::TimeScale(spic::settings::STANDARD_GAME_SPEED);
}

void ResetGameSpeedListener::OnKeyReleased()
{
}
