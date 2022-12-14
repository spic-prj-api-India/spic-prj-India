#include "Camera.hpp"

spic::Camera::Camera() : backgroundColor{ Color::black() }, GameObject()
{
	//retrieve aspectWidth and aspectHeight
}

void spic::Camera::BackgroundColor(const Color& color)
{
	this->backgroundColor = { color };
}

const spic::Color spic::Camera::BackgroundColor() const
{
	return this->backgroundColor;
}

void spic::Camera::BackgroundImage(const std::string& imagePath)
{
	backgroundImage = imagePath;
}

const std::string spic::Camera::BackgroundImage() const
{
	return backgroundImage;
}

const float spic::Camera::AspectWidth() const
{
	return -1;
}

const float spic::Camera::AspectHeight() const
{
	return -1;
}
