#include "Text.hpp"

spic::Text::Text()
	: UIObject()
	, text{ "" }
	, font{ "" }
	, size{ 0 }
	, alignment{ spic::Alignment::center }
	, color{ spic::Color::black() }
{
}

spic::Text::Text(const float width, const float height
	, const std::string& text
	, const std::string& font
	, const int size
	, const spic::Alignment alignment
	, const spic::Color& color)
	: UIObject(width, height)
	, text{ text }
	, font{ font }
	, size{ size }
	, alignment{ alignment }
	, color{ color }
{
}

const std::string spic::Text::_Text()
{
	return text;
}

const void spic::Text::_Text(const std::string& text)
{
	this->text = text;
}

const std::string spic::Text::Font()
{
	return this->font;
}

const void spic::Text::Font(const std::string& font)
{
	this->font = font;
}

const int spic::Text::Size()
{
	return this->size;
}

const void spic::Text::Size(const int size)
{
	this->size = size;
}

const spic::Alignment spic::Text::Alignment()
{
	return alignment;
}

const void spic::Text::Alignment(const spic::Alignment alignment)
{
	this->alignment = alignment;
}

const spic::Color spic::Text::Color()
{
	return this->color;
}

const void spic::Text::Color(const spic::Color color)
{
	this->color = color;
}
