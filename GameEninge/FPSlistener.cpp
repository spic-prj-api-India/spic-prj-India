#include "FPSlistener.hpp"

bool FPSListener::renderFps = true;

void FPSListener::OnKeyPressed()
{
	renderFps = !renderFps;
}

void FPSListener::OnKeyReleased()
{
}
