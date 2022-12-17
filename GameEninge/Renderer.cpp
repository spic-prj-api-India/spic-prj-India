#include "Renderer.hpp"
#include "RendererImpl.hpp"

void spic::internal::Rendering::Start()
{
	spic::internal::rendering::RendererImpl::GetInstance()->Start();
}

void spic::internal::Rendering::Exit()
{
	spic::internal::rendering::RendererImpl::GetInstance()->Exit();
}

void spic::internal::Rendering::Draw(GameObject* gameObject)
{
	spic::internal::rendering::RendererImpl::GetInstance()->DrawGameObject(gameObject);
}

void spic::internal::Rendering::UpdateCamera(Camera* camera)
{
	spic::internal::rendering::RendererImpl::GetInstance()->UpdateCamera(camera);
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

void spic::internal::Rendering::AddDebugLine(const spic::Point& start, const spic::Point& end)
{
	spic::internal::rendering::RendererImpl::GetInstance()->AddDebugLine(start, end);
}

void spic::internal::Rendering::DrawDebugLines()
{
	spic::internal::rendering::RendererImpl::GetInstance()->DrawDebugLines();
}

void spic::internal::Rendering::DrawSprite(const Transform* position, Sprite* sprite)
{
	spic::internal::rendering::RendererImpl::GetInstance()->DrawSprite(sprite, position);
}

void spic::internal::Rendering::Clean()
{
	spic::internal::rendering::RendererImpl::GetInstance()->Clean();
}

void spic::internal::Rendering::NewScene()
{
	spic::internal::rendering::RendererImpl::GetInstance()->NewScene();
}

void spic::internal::Rendering::Render()
{
	spic::internal::rendering::RendererImpl::GetInstance()->Render();
}

std::pair<float, float> spic::internal::Rendering::GetAspects()
{
	return std::pair<float, float>();
}
