#include "Renderer.hpp"
#include "RendererImpl.hpp"

using namespace spic::internal;

static std::unique_ptr<rendering::RendererImpl> impl = std::make_unique<rendering::RendererImpl>();


void spic::internal::Rendering::Start()
{
	impl->Start();
}

void spic::internal::Rendering::Exit()
{
	impl->Exit();
}

void spic::internal::Rendering::Draw(GameObject* gameObject)
{
	impl->DrawGameObject(gameObject);
}

void spic::internal::Rendering::UpdateCamera(Camera* camera)
{
	impl->UpdateCamera(camera);
}

void spic::internal::Rendering::AddDebugLine(const spic::Line& line, const spic::Color& color)
{
	impl->AddDebugLine(line, color);
}

void spic::internal::Rendering::AddDebugRect(const spic::Rect& rect, const double angle, const spic::Color& color)
{
	impl->AddDebugRect(rect, angle, color);
}

void spic::internal::Rendering::AddDebugCircle(const spic::Circle& circle, const spic::Color& color, const float pixelGap)
{
	impl->AddDebugCircle(circle, color, pixelGap);
}

void spic::internal::Rendering::AddDebugPoint(const spic::Point& point, const spic::Color& color)
{
	impl->AddDebugPoint(point, color);
}

void spic::internal::Rendering::DrawDebugShapes()
{
	impl->DrawDebugShapes();
}

void spic::internal::Rendering::DrawSprite(const Transform& position, Sprite* sprite)
{
	impl->DrawSprite(sprite, position);
}

void spic::internal::Rendering::Clean()
{
	impl->Clean();
}

void spic::internal::Rendering::NewScene()
{
	impl->NewScene();
}

void spic::internal::Rendering::Render()
{
	impl->Render();
}

std::pair<float, float> spic::internal::Rendering::GetAspects()
{
	return std::pair<float, float>();
}

void spic::internal::Rendering::DrawFps()
{
	impl->DrawFps();
}
