#ifndef RENDERERWINDOW_H_
#define RENDERERWINDOW_H_

#include "SDLPointers.hpp"
#include "Camera.hpp"
#include "Settings.hpp"
#include "GeneralHelper.hpp"
#include "RenderTextures.hpp"
#include "Defaults.hpp"
#include "RenderText.hpp"
#include "Circle.hpp"
#include "Rect.hpp"

// needs to be used for SDL
#undef main

namespace spic::internal::rendering::impl
{
	/**
	 * @brief The rendering class that is in charge of rendering basic shapes and displaying rendered stuff on the window
	*/
	class RenderingWindow
	{
	private:
		/**
		 * @brief sdl window ptr
		*/
		WindowPtr settings;

		/**
		 * @brief sdl renderer ptr
		*/
		RendererPtr renderer;

		/**
		 * @brief Camera of the window
		*/
		SDL_FRect windowCamera;

		/**
		 * @brief World camera settings
		*/
		SDL_FRect camera;
		float scaling;
		float rotation;
		Color backgroundColor;
		std::string backgroundImage;
		float aspectHeight;
		float aspectWidth;

		/**
		 * @brief Weak pointer to the RenderTextures class
		*/
		std::weak_ptr<RenderTextures> renderTextures;

		/**
		 * @brief Sets the renderer color
		 * @param color Of type color
		*/
		void DrawColor(const spic::Color& color) const;

		/**
		 * @brief Draws an point on the window.
		 * @param x X coordiant
		 * @param y Y coordiant
		*/
		void DrawPoint(const float x, const float y) const;

	public:
		/**
		 * @brief Sets all parameters (where possible) to zero except size. Size is 1.
		*/
		RenderingWindow();

		/**
		 * @brief Als calls exit.
		*/
		~RenderingWindow();
		RenderingWindow(const RenderingWindow& other) = delete; // copy constructor
		RenderingWindow(RenderingWindow&& other) noexcept = delete; // move constructor
		RenderingWindow& operator=(const RenderingWindow& other) = delete; // copy assignment
		RenderingWindow& operator=(RenderingWindow&& other) noexcept = delete;// move assignment
		
		/**
		 * @brief Quits all sdl sub systems
		*/
		void Exit();

		/**
		 * @brief Cleans the renderer
		*/
		void Clean();

		/**
		 * @brief Draws everything in the renderer's buffer to the window
		*/
		void Render();

		/**
		 * @brief Creates an renderer and initializes SDL
		 * @return The current active renderer
		*/
		RendererPtrWeak CreateWindow() noexcept(false);

		/**
		 * @brief Updates the window with values in the settings namespace.
		*/
		void UpdateWindow();

		/**
		 * @brief Updates the current active camera values from the camera object.  
		 * @param camera The current scene's camera object
		*/
		void UpdateCamera(const spic::Camera* camera);

		/**
		 * @brief If the SDL_FRect has intersection with the camera
		 * @param rect An random rectangle
		 * @return If it has intersection, it returns true
		*/
		bool RectHasIntersectionWithCamera(const SDL_FRect& rect) const;

		/**
		 * @brief If the SDL_FRect has intersection with the windowCamera
		 * @param rect An random rectangle
		 * @return If it has intersection, it returns true
		*/
		bool RectHasIntersectionWithWindow(const SDL_FRect& rect) const;

		/**
		 * @brief If the Point object has intersection with the windowCamera
		 * @param point An random Point
		 * @return If it has intersection, it returns true
		*/
		bool PointHasIntersectionWithWindow(const Point& point) const;

		/**
		 * @brief If the Point object has intersection with the camera
		 * @param point An random Point
		 * @return If it has intersection, it returns true
		*/
		bool PointHasIntersectionWithCamera(const Point& point) const;

		/**
		 * @brief Draws an line in world space
		 * @details Line is not drawn when line is not in camera view.
		 * @param start The start point of an line
		 * @param end The end point of an line
		 * @param colour The colour of the line
		*/
		void DrawLine(const spic::Point& start, const spic::Point& end, const spic::Color& color) const;

		/**
		 * @brief Draws a point in world space.
		 * @details Point is not drawn when x or y are not in camera view.
		 * @param x of point
		 * @param y of point
		 * @param color The color of the point
		*/
		void DrawPoint(const spic::Point& point, const spic::Color& color) const;


		/**
		 * @brief Draws an circle in world space
					using the mid point circle algorithm https://en.wikipedia.org/w/index.php?title=Midpoint_circle_algorithm
		 * @details Circle is not drawn when circle is not in camera view.
		 * @param circle Circle to be drawn
		 * @param pixelGap The gap (in pixels) between each point in the circle
		 * @param color The color of the circle
		*/
		void DrawCircle(const spic::Circle& circle, const float pixelGap, const spic::Color& color) const;

		/**
		 * @brief Draws an rectangle in world space
		 * @details Rectangle is not drawn when rectangle is not in camera view.
		 * @param rect The x, y, width, height of rectangle
		 * @param angle The angle of the square
		 * @param color The color of the square
		*/
		void DrawRect(const spic::Rect& rect, const double angle, const spic::Color& color);

		/**
		 * @brief Sets an RenderTextures reference in this class
		 * @param textures The RenderTextures shared_ptr
		*/
		void SetRenderTextures(std::shared_ptr<RenderTextures> textures);

		/**
		 * @brief Gets the current window camera
		 * @return The WindowCamera
		*/
		SDL_FRect GetWindowCamera() const;
		
		/**
		 * @brief Gets the current camera rectangle
		 * @return The camera 
		*/
		SDL_FRect GetCamera() const;

		/**
		 * @brief Gets the current scaling rate
		 * @return The scaling
		*/
		float GetScaling() const;

		/**
		 * @brief Adds an RenderTextures reference to this class
		 * @param renderTextures The RenderTextures reference
		*/
		void AddTexture(std::weak_ptr<RenderTextures> renderTextures);
	};
}
#endif // RENDERERWINDOW_H_