#include "FPSlistener.hpp"

bool FPSListener::renderFps = true;

void FPSListener::OnKeyPressed()
{
	if(renderFps)
		renderFps = false;
	else
		renderFps = true;
}

void FPSListener::OnKeyReleased()
{
}
