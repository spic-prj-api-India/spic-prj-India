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

void spic::internal::Rendering::AddDebugLine(const spic::Line& line, const spic::Color& color)
{
	spic::internal::rendering::RendererImpl::GetInstance()->AddDebugLine(line, color);
}

void spic::internal::Rendering::AddDebugRect(const spic::Rect& rect, const double angle, const spic::Color& color)
{
	spic::internal::rendering::RendererImpl::GetInstance()->AddDebugRect(rect, angle, color);
}

void spic::internal::Rendering::AddDebugCircle(const spic::Circle& circle, const spic::Color& color, const float pixelGap)
{
	spic::internal::rendering::RendererImpl::GetInstance()->AddDebugCircle(circle, color, pixelGap);
}

void spic::internal::Rendering::AddDebugPoint(const spic::Point& point, const spic::Color& color)
{
	spic::internal::rendering::RendererImpl::GetInstance()->AddDebugPoint(point, color);
}

void spic::internal::Rendering::DrawDebugShapes()
{
	spic::internal::rendering::RendererImpl::GetInstance()->DrawDebugShapes();
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
