#include "RendererWindow.hpp"
#include "Debug.hpp"
#include "Settings.hpp"
#include "GeneralHelper.hpp"

namespace spic::internal::rendering::impl
{
	void RenderingWindow::DrawColor(const spic::Color& color) const
	{
		using namespace spic::helper_functions::general_helper;

		if (auto texture = this->renderTextures.lock(); texture != nullptr)
		{
			const auto _color = texture->ConvertsColor(color);

			SDL_SetRenderDrawColor(renderer.get()
				, _color.r
				, _color.g
				, _color.b
				, _color.a);
		}
	}

	void RenderingWindow::DrawPoint(const float x, const float y) const
	{
		SDL_RenderDrawPointF(renderer.get(), x, y);
	}

	RenderingWindow::RenderingWindow() : camera{ 0, 0, 0, 0 }, backgroundColor{ 0,0,0,1 }, backgroundImage{ "" }, scaling{ 1 }, rotation{ 0 }
	{
	}

	RenderingWindow::~RenderingWindow()
	{
		try
		{
			this->Exit();
		}
		catch (...)
		{
			//TODO add dev
		}
	}

	void RenderingWindow::Exit()
	{
		SDL_Quit();
	}

	void RenderingWindow::Clean()
	{
		if (auto texture = this->renderTextures.lock(); texture != nullptr)
		{
			SDL_RenderClear(renderer.get());

			if (!backgroundImage.empty())
			{
				auto _texture = texture->LoadTexture(backgroundImage);
				SDL_RenderCopy(renderer.get(), _texture, NULL, NULL);
			}

			this->DrawColor(this->backgroundColor);
		}
	}

	void RenderingWindow::Render()
	{
		this->DrawColor(this->backgroundColor);

		SDL_RenderPresent(renderer.get());
	}

	RendererPtrWeak RenderingWindow::CreateWindow() noexcept(false)
	{
		// sets up video
		if (SDL_Init(SDL_INIT_VIDEO != 0))
		{
			spic::debug::LogError(SDL_GetError());
			exit(-1);
		}
		
		// sets up window
		const SDL_WindowFlags w_flags = SDL_WindowFlags(SDL_WINDOW_ALLOW_HIGHDPI);
		settings = WindowPtr(SDL_CreateWindow(spic::settings::WINDOW_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, spic::settings::WINDOW_WIDTH, spic::settings::WINDOW_HEIGHT, w_flags));
		if (settings.get() == nullptr) {
			spic::debug::LogError(SDL_GetError());
			exit(-1);
		}

		SDL_SetWindowAlwaysOnTop(settings.get(),
			(SDL_bool)spic::settings::SET_ON_TOP);

		// creates renderer
		SDL_RendererFlags rendererFlags = (SDL_RendererFlags)(SDL_RENDERER_ACCELERATED);
		this->renderer = RendererPtr(SDL_CreateRenderer(settings.get(), -1, rendererFlags), SDL_Deleter());
		if (this->renderer.get() == nullptr) {
			spic::debug::LogError(SDL_GetError());
			exit(-1);
		}

		// updates the window rectangle
		UpdateWindow();

		return this->renderer;
	}

	void RenderingWindow::UpdateWindow()
	{
		Uint32 window_flags = -1;

		switch (spic::settings::SELECTOR)
		{
		case spic::settings::FullScreenType::BORDERLESS:
			window_flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
			break;
		case spic::settings::FullScreenType::FULLSCREEN:
			window_flags = SDL_WINDOW_FULLSCREEN;
			break;
		case spic::settings::FullScreenType::WINDOWED:
			window_flags = 0;
			break;
		}

		if (window_flags != -1)
			SDL_SetWindowFullscreen(settings.get(),
				window_flags);

		int width, height = 0;
		SDL_GetWindowSize(settings.get(), &width, &height);
		this->windowCamera = { 0, 0, static_cast<float>(width), static_cast<float>(height) };
		this->camera.w = static_cast<float>(width);
		this->camera.h = static_cast<float>(height);

		spic::settings::WINDOW_HEIGHT = height;
		spic::settings::WINDOW_WIDTH = width;
	}

	void RenderingWindow::UpdateCamera(const spic::Camera* camera)
	{
		auto transform = camera->Transform().get();
		const auto pos = transform->position;
		this->scaling = transform->scale;
		this->rotation = transform->rotation;

		int width, height = 0;
		SDL_GetWindowSize(settings.get(), &width, &height);
		this->camera =
		{ pos.x
		, pos.y
		, static_cast<float>(width)
		, static_cast<float>(height) };

		this->backgroundColor = camera->BackgroundColor();
		this->backgroundImage = camera->BackgroundImage();
	}

	bool RenderingWindow::RectHasIntersectionWithCamera(const SDL_FRect& rect) const
	{
		if (SDL_HasIntersectionF(&rect, &this->camera))
			return true;

		return false;
	}

	bool RenderingWindow::RectHasIntersectionWithWindow(const SDL_FRect& rect) const
	{
		if (SDL_HasIntersectionF(&rect, &this->windowCamera))
			return true;

		return false;
	}

	bool RenderingWindow::PointHasIntersectionWithWindow(const Point& point) const
	{
		SDL_FPoint startPoint = { point.x , point.y };
		if (!SDL_PointInFRect(&startPoint, &this->windowCamera))
			return true;

		return false;
	}

	bool RenderingWindow::PointHasIntersectionWithCamera(const Point& point) const
	{
		SDL_FPoint startPoint = { point.x , point.y };
		if (!SDL_PointInFRect(&startPoint, &this->camera))
			return true;

		return false;
	}

	void RenderingWindow::DrawLine(const spic::Point& start, const spic::Point& end, const spic::Color& color) const
	{
		// checks if the begin, endpoint or center is in the window 
		if (!this->PointHasIntersectionWithCamera(start)
			&& 
			!this->PointHasIntersectionWithCamera(end)
			&&
			!this->PointHasIntersectionWithCamera(start.MidPoint(end)))
			return;

		// start point to window point
		const float begin_x = start.x - this->camera.x;
		const float begin_y = start.y - this->camera.y;

		// end point to window point
		const float end_x = end.x - this->camera.x;
		const float end_y = end.y - this->camera.y;

		// converts color to sdl color
		this->DrawColor(color);

		SDL_RenderDrawLineF(renderer.get()
			, begin_x
			, begin_y
			, end_x
			, end_y);
	}

	void RenderingWindow::DrawPoint(const spic::Point& point, const spic::Color& color) const
	{
		if (!this->PointHasIntersectionWithCamera(point))
			return;

		// start point to window point
		const float x = point.x - this->camera.x;
		const float y = point.y - this->camera.y;

		// converts color to sdl color
		this->DrawColor(color);
		this->DrawPoint(x, y);
	}

	void RenderingWindow::DrawRect(const spic::Rect& rect, const double angle, const spic::Color& color)
	{
		if (auto texture = this->renderTextures.lock(); texture != nullptr)
		{
			SDL_FRect dstRect = SDL_FRect(rect.x, rect.y, rect.w, rect.h);
			if (!this->RectHasIntersectionWithCamera(dstRect))
				return;

			dstRect.x = dstRect.x - this->camera.x;
			dstRect.y = dstRect.y - this->camera.y;
			const double angleInDeg = spic::helper_functions::general_helper::RAD2DEG<double>(angle);

			auto _texture = texture->LoadTexture(spic::internal::defaults::RECT_TEXTURE);
			texture->SetTextureColor(_texture, color);

			texture->RenderTexture(_texture, NULL, &dstRect, angleInDeg, SDL_FLIP_NONE);
		}
	}

	void RenderingWindow::DrawCircle(const spic::Circle& circle, const float pixelGap, const spic::Color& color) const
	{
		const float diameter = circle.radius * 2.0f;
		SDL_FRect dstCenter = SDL_FRect(circle.center.x - circle.radius
			, circle.center.y - circle.radius, diameter, diameter);

		if (!this->RectHasIntersectionWithCamera(dstCenter))
			return;

		dstCenter.x = dstCenter.x + circle.radius - this->camera.x;
		dstCenter.y = dstCenter.y + circle.radius - this->camera.y;

		this->DrawColor(color);

		// Pixel gap configures how precise the circle is drawn
		float x = circle.radius - pixelGap;
		float y = 0.0f;
		float dx = pixelGap;
		float dy = pixelGap;
		// if decision is above zero: y++, otherwise x++
		float decisionOver2 = dx - diameter;

		while (x >= y)
		{
			DrawPoint(dstCenter.x + x, dstCenter.y + y);
			DrawPoint(dstCenter.x + y, dstCenter.y + x);
			DrawPoint(dstCenter.x - y, dstCenter.y + x);
			DrawPoint(dstCenter.x - x, dstCenter.y + y);
			DrawPoint(dstCenter.x - x, dstCenter.y - y);
			DrawPoint(dstCenter.x - y, dstCenter.y - x);
			DrawPoint(dstCenter.x + y, dstCenter.y - x);
			DrawPoint(dstCenter.x + x, dstCenter.y - y);

			if (decisionOver2 <= 0.0f)
			{
				y += pixelGap;
				decisionOver2 += dy;
				dy += 2 * pixelGap;
			}
			if (decisionOver2 > 0.0f)
			{
				x -= pixelGap;
				dx += 2 * pixelGap;
				decisionOver2 += (-diameter) + dx;
			}
		}
	}

	void RenderingWindow::SetRenderTextures(std::shared_ptr<RenderTextures> textures)
	{
		this->renderTextures = std::move(textures);
	}

	SDL_FRect RenderingWindow::GetWindowCamera() const
	{
		return this->windowCamera;
	}

	SDL_FRect RenderingWindow::GetCamera() const
	{
		return this->camera;
	}

	float RenderingWindow::GetScaling() const
	{
		return this->scaling;
	}

	void RenderingWindow::AddTexture(std::weak_ptr<RenderTextures> renderTextures)
	{
		this->renderTextures = std::move(renderTextures);
	}
}