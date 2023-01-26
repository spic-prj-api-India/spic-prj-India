#include "Renderer.hpp"
#include "RendererGameObjects.hpp"
#include "RendererWindow.hpp"
#include "RenderText.hpp"
#include "RenderTextures.hpp"
#include "Settings.hpp"

namespace spic::internal
{
	static std::shared_ptr<rendering::impl::RenderingWindow> window;
	static std::shared_ptr<rendering::impl::RenderTextures> textures;
	static std::shared_ptr<rendering::impl::RenderingText> text;
	static std::shared_ptr<rendering::impl::RendererGameObjects> objects;

	static std::vector<std::pair<spic::Line, spic::Color>> debugLines;
	static std::vector<std::pair<std::pair<spic::Rect, double>, spic::Color>> debugRects;
	static std::vector<std::pair<std::pair<spic::Circle, float>, spic::Color>> debugCircles;
	static std::vector<std::pair<spic::Point, spic::Color>> debugPoints;

	void Rendering::Start()
	{
		if (window == nullptr)
		{
			window = std::move(std::make_shared<rendering::impl::RenderingWindow>());
			auto renderer = window->CreateWindow();

			textures = std::move(std::make_shared<rendering::impl::RenderTextures>(renderer));

			window->AddTexture(textures);

			text = std::move(std::make_shared<rendering::impl::RenderingText>(renderer));

			objects = std::move(std::make_shared<rendering::impl::RendererGameObjects>(textures, window, text));
		}
	}

	void Rendering::Exit()
	{
		if (auto wind = window.get(); wind != nullptr)
		{
			wind->Exit();
			window = nullptr;
			textures = nullptr;
			text = nullptr;
			objects = nullptr;
		}
	}

	void Rendering::Draw(GameObject* gameObject)
	{
		if (auto ob = objects.get(); ob != nullptr)
			ob->DrawGameObject(gameObject);
	}

	void Rendering::UpdateCamera(Camera* camera)
	{
		if (auto wind = window.get(); wind != nullptr)
			wind->UpdateCamera(camera);
	}

	void Rendering::AddDebugLine(const spic::Line& line, const spic::Color& color)
	{
		std::pair<spic::Line, spic::Color> debugLine = { line, color };
		debugLines.emplace_back(debugLine);
	}

	void Rendering::AddDebugRect(const spic::Rect& rect, const double angle, const spic::Color& color)
	{
		std::pair<std::pair<spic::Rect, double>, spic::Color> debugRect = { { rect, angle }, color };
		debugRects.emplace_back(debugRect);
	}

	void spic::internal::Rendering::AddDebugCircle(const spic::Circle& circle, const spic::Color& color, const float pixelGap)
	{
			std::pair<std::pair<spic::Circle, float>, spic::Color> debugCircle = { { circle, pixelGap }, color };
			debugCircles.emplace_back(debugCircle);
	}

	void Rendering::AddDebugPoint(const spic::Point& point, const spic::Color& color)
	{
		std::pair<spic::Point, spic::Color> debugPoint = { point, color };
		debugPoints.emplace_back(debugPoint);
	}

	void Rendering::DrawDebugShapes()
	{
		if (auto wind = window.get(); wind != nullptr)
		{
			debugLines.clear();
			debugRects.clear();
			debugPoints.clear();
			return;
		}

		for (const auto& debugLine : debugLines) 
		{
			const Line& line = debugLine.first;
			window->DrawLine(line.start, line.end, debugLine.second);
		}
		debugLines.clear();

		for (const auto& debugRect : debugRects) 
		{
			const Rect& rect = debugRect.first.first;
			const double angle = debugRect.first.second;
			window->DrawRect(rect, angle, debugRect.second);
		}
		debugRects.clear();

		for (const auto& debugCircle : debugCircles) 
		{
			const Circle& circle = debugCircle.first.first;
			const float pixelGap = debugCircle.first.second;
			window->DrawCircle(circle, pixelGap, debugCircle.second);
		}
		debugCircles.clear();

		for (const auto& debugPoint : debugPoints) 
		{
			const Point& point = debugPoint.first;
			window->DrawPoint(point, debugPoint.second);
		}
		debugPoints.clear();
	}

	void Rendering::DrawSprite(const Transform& position, const Sprite* sprite)
	{
		if (auto ob = objects.get(); ob != nullptr)
			ob->DrawSprite(sprite, &position);
	}

	void Rendering::Clean()
	{
		if (auto wind = window.get(); wind != nullptr)
			wind->Clean();
	}

	void Rendering::NewScene()
	{
		if (auto texture = textures.get(); texture != nullptr)
			texture->Reset();

		if (auto tex = text.get(); tex != nullptr)
			text->Reset();
	}

	void Rendering::Render()
	{
		if (auto wind = window.get(); wind != nullptr)
			wind->Render();

		if (!spic::settings::KEEP_TEXTURES_AND_FONTS_LOADED)
			NewScene();
	}

	void Rendering::DrawFps()
	{
		if (auto tex = text.get(); tex != nullptr)
			tex->DrawFps();
	}
}
