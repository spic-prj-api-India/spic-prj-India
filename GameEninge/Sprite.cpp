#include "Sprite.hpp"

spic::Sprite::Sprite()
	: sprite{ ""}
	, color{ spic::Color::white()}
	, flipX{ false }
	, flipY{ false }
	, sortingLayer{ 0 }
	, orderInLayer{ 0 }
	, x{ 0 }
	, y{ 0 }
	, height{ 0 }
	, width{ 0 }
{
}

spic::Sprite::Sprite(const std::string& sprite
	, const bool flipX
	, const bool flipY
	, const int sortingLayer
	, const int orderInLayer
	, const int x
	, const int y
	, const int height
	, const int width)
	: sprite{sprite}
	, color{color}
	, flipX{flipX}
	, flipY{flipY}
	, sortingLayer{ sortingLayer }
	, orderInLayer{ orderInLayer }
	, x{x}
	, y{y}
	, height{ height }
	, width{ width }
{
}

spic::Sprite::Sprite(const spic::Color& color
	, const bool flipX
	, const bool flipY
	, const int sortingLayer
	, const int orderInLayer
	, const int x
	, const int y
	, const int height
	, const int width) :
	  color{ color }
	, flipX{ flipX }
	, flipY{ flipY }
	, sortingLayer{ sortingLayer }
	, orderInLayer{ orderInLayer }
	, x{ x }
	, y{ y }
	, height{ height }
	, width{ width }
{
}

const std::string spic::Sprite::_Sprite() const
{
	return this->sprite;
}

const void spic::Sprite::_Sprite(const std::string& sprite)
{
	this->sprite = sprite;
}

const spic::Color spic::Sprite::Color() const
{
	return this->color;
}

const void spic::Sprite::Color(const spic::Color& color)
{
	this->color = color;
}

const bool spic::Sprite::FlipX() const
{
	return this->flipX;
}

const void spic::Sprite::FlipX(const bool flipx)
{
	this->flipX = flipx;
}

const bool spic::Sprite::FlipY() const
{
	return this->flipY;
}

const void spic::Sprite::FlipY(const bool flipy)
{
	flipY = flipy;
}

const int spic::Sprite::SortingLayer() const
{
	return this->sortingLayer;
}

const void spic::Sprite::SortingLayer(const int sortingLayer)
{
	this->sortingLayer = sortingLayer;
}

const int spic::Sprite::OrderInLayer() const
{
	return this->orderInLayer;
}

const void spic::Sprite::OrderInLayer(const int orderInLayer)
{
	this->orderInLayer = orderInLayer;
}

const int spic::Sprite::X() const
{
	return x;
}

const void spic::Sprite::X(int newX)
{
	x = newX;
}

const int spic::Sprite::Y() const
{
	return y;
}

const void spic::Sprite::Y(int newY)
{
	y = newY;
}

const int spic::Sprite::Height() const
{
	return height;
}

const void spic::Sprite::Height(int newHeight)
{
	height = newHeight;
}

const int spic::Sprite::Width() const
{
	return width;
}

const void spic::Sprite::Width(int newWidth)
{
	width = newWidth;
}

bool spic::Sprite::operator<(Sprite const& a)
{
	if (this->orderInLayer < a.orderInLayer)
		return true;

	if (this->orderInLayer > a.orderInLayer)
		return false;

	if (this->sortingLayer < a.sortingLayer)
		return true;

	if (this->sortingLayer > a.sortingLayer)
		return true;

	return false;
}
