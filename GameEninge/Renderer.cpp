#include "Renderer.hpp"
#include "RendererImpl.hpp"

void spic::internal::Rendering::Start(const spic::window::WindowValues* values)
{
	spic::internal::rendering::RendererImpl::GetInstance()->Start(values);
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

void spic::internal::Rendering::DrawLine(const spic::Point& start, const spic::Point& end, const spic::Color& color)
{
	spic::internal::rendering::RendererImpl::GetInstance()->DrawLine(start, end, color);
}

void spic::internal::Rendering::DrawRect(const spic::Rect& rect, const double angle, const spic::Color& color)
{
	spic::internal::rendering::RendererImpl::GetInstance()->DrawRect(rect, angle, color);
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
