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
	return void();
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
	return this->x;
}

const void spic::Sprite::X(int x)
{
	return void();
}

const int spic::Sprite::Y() const
{
	return 0;
}

const int spic::Sprite::Y(int x)
{
	return 0;
}

const int spic::Sprite::Height() const
{
	return 0;
}

const int spic::Sprite::Height(int x)
{
	return 0;
}

const int spic::Sprite::Width()
{
	return 0;
}

const int spic::Sprite::Width(int x) const
{
	return 0;
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
