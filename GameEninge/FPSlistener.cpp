#include "FPSlistener.hpp"

bool FPSListener::renderFps = true;

void FPSListener::OnKeyPressed()
{
	if(renderFps)
		renderFps = true;
	else
		renderFps = false;
}

void FPSListener::OnKeyReleased()
{
}
