#include "FPSlistener.hpp"

using namespace spic::internal::input;

bool FPSListener::renderFps = true;

void FPSListener::OnKeyPressed()
{
	renderFps = !renderFps;
}

void FPSListener::OnKeyReleased()
{
}
