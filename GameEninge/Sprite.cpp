#include "Sprite.hpp"

spic::Sprite::Sprite()
	: sprite{ "" }
	, color{ spic::Color::white() }
	, flipX{ false }
	, flipY{ false }
	, sortingLayer{ 0 }
	, orderInLayer{ 0 }
	, x{ 0 }
	, y{ 0 }
	, width{ 0 }
	, height{ 0 }
	, displayHeight{ 0 }
	, displayWidth{ 0 }
{
}

spic::Sprite::Sprite(const std::string& sprite
	, const int sortingLayer
	, const int orderInLayer
	, const spic::Color& color
	, const bool flipX
	, const bool flipY
	, const int x
	, const int y
	, const int width
	, const int height)
	: sprite{ sprite }
	, color{ color }
	, flipX{ flipX }
	, flipY{ flipY }
	, sortingLayer{ sortingLayer }
	, orderInLayer{ orderInLayer }
	, x{ x }
	, y{ y }
	, width{ width }
	, height{ height }
	, displayHeight { 0 }
	, displayWidth { 0 }
{
}

const std::string spic::Sprite::_Sprite() const
{
	return this->sprite;
}

void spic::Sprite::_Sprite(const std::string& sprite)
{
	this->sprite = sprite;
}

const spic::Color spic::Sprite::Color() const
{
	return this->color;
}

void spic::Sprite::Color(const spic::Color& color)
{
	this->color = color;
}

const bool spic::Sprite::FlipX() const
{
	return this->flipX;
}

void spic::Sprite::FlipX(const bool flipx)
{
	this->flipX = flipx;
}

const bool spic::Sprite::FlipY() const
{
	return this->flipY;
}

void spic::Sprite::FlipY(const bool flipy)
{
	flipY = flipy;
}

const int spic::Sprite::SortingLayer() const
{
	return this->sortingLayer;
}

void spic::Sprite::SortingLayer(const int sortingLayer)
{
	this->sortingLayer = sortingLayer;
}

const int spic::Sprite::OrderInLayer() const
{
	return this->orderInLayer;
}

void spic::Sprite::OrderInLayer(const int orderInLayer)
{
	this->orderInLayer = orderInLayer;
}

const int spic::Sprite::X() const
{
	return this->x;
}

const void spic::Sprite::X(int newX)
{
	this->x = newX;
}

const int spic::Sprite::Y() const
{
	return this->y;
}

const void spic::Sprite::Y(int newY)
{
	this->y = newY;
}

const int spic::Sprite::Height() const
{
	return this->height;
}

const void spic::Sprite::Height(int newHeight)
{
	this->height = newHeight;
}

const int spic::Sprite::Width() const
{
	return this->width;
}

const void spic::Sprite::Width(int newWidth)
{
	this->width = newWidth;
}

const float spic::Sprite::DisplayHeight() const
{
	return this->displayHeight;
}

const void spic::Sprite::DisplayHeight(float newWidth)
{
	this->displayHeight = newWidth;
}

const float spic::Sprite::DisplayWidth() const
{
	return this->displayWidth;
}

const void spic::Sprite::DisplayWidth(float newWidth)
{
	this->displayWidth = newWidth;
}