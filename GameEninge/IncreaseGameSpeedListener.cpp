#include "IncreaseGameSpeedListener.hpp"
#include "Time.hpp"
#include "Settings.hpp"

using namespace spic::internal::input;

void IncreaseGameSpeedListener::OnKeyPressed()
{
	const auto now = spic::Time::TimeScale();

	spic::Time::TimeScale(now + spic::settings::GAME_SPEED_INCREASE_AND_DECREASE_RATE);
}

void IncreaseGameSpeedListener::OnKeyReleased()
{

}