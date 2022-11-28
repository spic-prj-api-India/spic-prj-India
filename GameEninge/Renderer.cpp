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

void spic::internal::Rendering::SetBackgroundColor()
{
	spic::internal::rendering::RendererImpl::GetInstance()->SetBackgroundColor();
}

void spic::internal::Rendering::DrawLine(const Point* start, const Point* end, const Color* colour)
{
	spic::internal::rendering::RendererImpl::GetInstance()->DrawLine(start,end, colour);
}

void spic::internal::Rendering::DrawSprite(const Transform* position, const bool isUi, Sprite* sprite)
{
	spic::internal::rendering::RendererImpl::GetInstance()->DrawSprite(sprite, isUi, position );
}

void spic::internal::Rendering::DrawAnimator(const Transform* position, const bool isUi, Animator* animator)
{
	spic::internal::rendering::RendererImpl::GetInstance()->DrawAnimator(animator, isUi, position);
}

void spic::internal::Rendering::DrawText(Text* text, const bool isUi)
{
	spic::internal::rendering::RendererImpl::GetInstance()->DrawText(text);
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
