#include "Sprite.hpp"

spic::Sprite::Sprite()
	: sprite{ ""}
	, color{ spic::Color::white()}
	, flipX{ false }
	, flipY{ false }
	, sortingLayer{ -1 }
	, orderInLayer{ -1 }
	, x{ 0 }
	, y{ 0 }
	, height{ 0 }
	, width{ 0 }
{
}

spic::Sprite::Sprite(const std::string& sprite
	, const spic::Color& color
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
	return void();
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

void spic::Sprite::X(int x)
{
	this->x = x;
}

const int spic::Sprite::Y() const
{
	return this->y;
}

void spic::Sprite::Y(int y)
{
	this->y = y;
}

const int spic::Sprite::Height() const
{
	return height;
}

void spic::Sprite::Height(int height)
{
	this->height = height;
}

const int spic::Sprite::Width() const
{
	return this->width;
}

void spic::Sprite::Width(int width)
{
	this->width = width;
}