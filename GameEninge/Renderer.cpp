#include "Renderer.hpp"
#include "RendererImp.hpp"

void spic::internal::Rendering::Start(const spic::window::WindowValues* values)
{
	spic::internal::rendering::RendererImp::GetInstance()->Start(values);
}

void spic::internal::Rendering::Exit()
{
	spic::internal::rendering::RendererImp::GetInstance()->Exit();
}

void spic::internal::Rendering::Draw(GameObject* gameObject)
{
	spic::internal::rendering::RendererImp::GetInstance()->DrawGameObject(gameObject);
}

void spic::internal::Rendering::UpdateCamera(Camera* camera)
{
	spic::internal::rendering::RendererImp::GetInstance()->UpdateCamera(camera);
}

void spic::internal::Rendering::SetBackgroundColor()
{
	spic::internal::rendering::RendererImp::GetInstance()->SetBackgroundColor();
}

void spic::internal::Rendering::DrawLine(const Point* start, const Point* end, const Color* colour)
{
	spic::internal::rendering::RendererImp::GetInstance()->DrawLine(start,end, colour);
}

void spic::internal::Rendering::DrawSprite(const Transform* position, const bool isUi, Sprite* sprite)
{
	spic::internal::rendering::RendererImp::GetInstance()->DrawSprite(sprite, isUi, position );
}

void spic::internal::Rendering::DrawAnimator(const Transform* position, const bool isUi, Animator* animator)
{
	spic::internal::rendering::RendererImp::GetInstance()->DrawAnimator(animator, isUi, position);
}

void spic::internal::Rendering::DrawText(Text* text, const bool isUi)
{
	spic::internal::rendering::RendererImp::GetInstance()->DrawText(text);
}

void spic::internal::Rendering::Clean()
{
	spic::internal::rendering::RendererImp::GetInstance()->Clean();
}

void spic::internal::Rendering::NewScene()
{
	spic::internal::rendering::RendererImp::GetInstance()->NewScene();
}

void spic::internal::Rendering::Render()
{
	spic::internal::rendering::RendererImp::GetInstance()->Render();
}

std::pair<float, float> spic::internal::Rendering::GetAspects()
{
	return std::pair<float, float>();
}
