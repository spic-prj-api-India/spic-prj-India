#include "Renderer.hpp"
#include "RendererImpl.hpp"

using namespace spic::internal;

static std::unique_ptr<rendering::RendererImpl> impl = std::make_unique<rendering::RendererImpl>();


void spic::internal::Rendering::Start(const spic::window::WindowValues* values)
{
	impl->Start(values);
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

void spic::internal::Rendering::DrawLine(const Point* start, const Point* end, const Color* colour)
{
	impl->DrawLine(start, end, colour);
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
