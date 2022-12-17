#include "Debug.hpp"
#include "Renderer.hpp"

using namespace spic;

void Debug::DrawLine(const spic::Point& start, const spic::Point& end, const spic::Color& color)
{
	spic::internal::Rendering::AddDebugLine(start, end);
}