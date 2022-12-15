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

void spic::internal::Rendering::DrawLine(const Point* start, const Point* end, const Color* colour)
{
	spic::internal::rendering::RendererImpl::GetInstance()->DrawLine(start,end, colour);
}

void spic::internal::Rendering::DrawSprite(const Transform* position, Sprite* sprite)
{
	spic::internal::rendering::RendererImpl::GetInstance()->DrawSprite(sprite, position );
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

void spic::internal::Rendering::Delay()
{
	spic::internal::rendering::RendererImpl::GetInstance()->Delay();
}

std::pair<float, float> spic::internal::Rendering::GetAspects()
{
	return std::pair<float, float>();
}

void spic::internal::Rendering::DrawFps()
{
	spic::internal::rendering::RendererImpl::GetInstance()->RenderFps();
}
