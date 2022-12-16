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

void spic::internal::Rendering::DrawRect(const spic::Rect& rect, const double angle, const spic::Color& color)
{
	spic::internal::rendering::RendererImpl::GetInstance()->DrawRect(rect, angle, color);
}

void spic::internal::Rendering::DrawCircle(const spic::Point& center, const float radius, const spic::Color& color, const float pixelGap)
{
	spic::internal::rendering::RendererImpl::GetInstance()->DrawCircle(center, radius, pixelGap, color);
}

void spic::internal::Rendering::DrawPoint(const spic::Point& point, const spic::Color& color)
{
	spic::internal::rendering::RendererImpl::GetInstance()->DrawPoint(point, color);
}

void spic::internal::Rendering::DrawLine(const spic::Point& start, const spic::Point& end, const spic::Color& color)
{
	spic::internal::rendering::RendererImpl::GetInstance()->DrawLine(start, end, color);
}

void spic::internal::Rendering::DrawSprite(const Transform* position, Sprite* sprite)
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
	impl->RenderFps();
}
