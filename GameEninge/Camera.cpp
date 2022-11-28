#include "Camera.hpp"

spic::Camera::Camera() : backgroundColor{ Color::black() }, GameObject()
{
	//retrieve aspectWidth and aspectHeight
}

void spic::Camera::BackgroundColor(const Color& color)
{
	this->backgroundColor = { color };
}

const spic::Color spic::Camera::BackgroundColor()
{
	return this->backgroundColor;
}

const float spic::Camera::AspectWidth()
{
	return -1;
}

const float spic::Camera::AspectHeight()
{
	return -1;
}
