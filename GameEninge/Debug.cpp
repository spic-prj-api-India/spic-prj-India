#include "Debug.hpp"
#include "Renderer.hpp"

using namespace spic;

void Debug::DrawLine(const spic::Point& start, const spic::Point& end, const spic::Color& color)
{
	spic::internal::Rendering::AddDebugLine({start, end}, color);
}

void Debug::DrawRect(const Rect& rect, const double angle, const Color& color)
{
	spic::internal::Rendering::AddDebugRect(rect, angle, color);
}

void Debug::DrawCircle(const Circle& circle, const Color& color, const float pixelGap)
{
	spic::internal::Rendering::AddDebugCircle(circle, color, pixelGap);
}

void Debug::DrawPoint(const spic::Point& point, const spic::Color& color)
{
	spic::internal::Rendering::AddDebugPoint(point, color);
}