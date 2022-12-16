#ifndef RENDERERIMPL_H_
#define RENDERERIMPL_H_

#include <mutex>
#include <string>
#include <memory>
#include <map>
#include "GameObject.hpp"
#include <SDL2/SDL.h>
#include "Scene.hpp"
#include <SDL2/SDL_image.h>
#include "Animator.hpp"
#include "Time.hpp"
#include <SDL2/SDL_ttf.h>
#include "Text.hpp"
#include "Rect.hpp"

// needs to be used for SDL
#undef main

/**
 * @brief The internal rendering namespace
*/
namespace spic::internal::rendering {
	/**
	 * @brief Deleters for SDL stuff
	*/
	struct SDL_Deleter {
		void operator()(SDL_Surface* ptr) { if (ptr) SDL_FreeSurface(ptr); }
		void operator()(SDL_Texture* ptr) { if (ptr) SDL_DestroyTexture(ptr); }
		void operator()(SDL_Renderer* ptr) { if (ptr) SDL_DestroyRenderer(ptr); }
		void operator()(SDL_Window* ptr) { if (ptr) SDL_DestroyWindow(ptr); }
		void operator()(SDL_RWops* ptr) { if (ptr) SDL_RWclose(ptr); }
		void operator()(TTF_Font* ptr) { if (ptr) TTF_CloseFont(ptr); }
	};

	/**
	 * @brief unique_ptr for SDL stuff
	*/
	using SurfacePtr = std::unique_ptr<SDL_Surface, SDL_Deleter>;
	using TexturePtr = std::unique_ptr<SDL_Texture, SDL_Deleter>;
	using RendererPtr = std::unique_ptr<SDL_Renderer, SDL_Deleter>;
	using WindowPtr = std::unique_ptr<SDL_Window, SDL_Deleter>;
	using RWopsPtr = std::unique_ptr<SDL_RWops, SDL_Deleter>;
	using FontPtr = std::unique_ptr<TTF_Font, SDL_Deleter>;

	/**
	 * @brief Render singelton
	 * @details Holds the implemntation for SDL (TODO: split in different classes)
	*/
	class RendererImpl
	{
		/**
		 * The Singleton's constructor/destructor should always be private to
		 * prevent direct construction/desctruction calls with the `new`/`delete`
		 * operator.
		*/
	private:
		static RendererImpl* pinstance_;
		static std::mutex mutex_;

		/**
		 * @brief Time related
		*/
		double lastTick;
		double deltatime;

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
		 * @brief sdl window ptr
		*/
		WindowPtr window;

		/**
		 * @brief sdl renderer ptr
		*/
		RendererPtr renderer;

		/**
		 * @brief Texture map
		*/
		std::map<std::string, TexturePtr> textures;

		TexturePtr missingTexture;

		/**
		 * @brief Font Map
		*/
		std::map<std::string, FontPtr> fonts;

		/**
		 * @brief Camera of the window
		*/
		SDL_FRect windowCamera;

		/**
		 * @brief Mutex for making the private instance of this class thread safe
		*/
		std::mutex mutex_rendering;

	protected:
		RendererImpl() noexcept(false);
		~RendererImpl();

	private:
		/**
		 * @brief Sets the backgroundColour
		 * @details should be called first after clean
		*/
		void SetBackgroundColor();

		/**
		 * @brief Draws all static sprites of a gameObject
		 * @param gameObject The gameobject
		 * @param isUiObject If it is an Uiobject
		*/
		void DrawSprites(GameObject* gameObject, const bool isUiObject);

		/**
		 * @brief Draws an sprite
		 * @param sprite The sprite to draw
		 * @param transform Contains position and rotation
		 * @param texture Texture that will be drawn
		 * @param dstRect Coordinates of sprite in texture
		 * @param sourceRect Coordinates of sprite in window
		*/
		void DrawSprite(const Sprite* sprite, const Transform* transform, SDL_Texture* texture,
			SDL_FRect* dstRect, SDL_Rect* sourceRect = NULL);

		/**
		 * @brief Loads textures in
		 * @param sprite The sprite to load
		 * @return an texture ptr
		*/
		SDL_Texture* LoadTexture(const std::string& sprite);

		/**
		 * @brief A font file
		 * @details TODO: use tt
		 * @param font font The font name
		 * @param size The size of the font
		 * @return
		*/
		TTF_Font* LoadFont(const std::string& font, const int size);

		/**
		 * @brief Gets size of texture
		 * @param texture
		 * @return An point object where x is the width en y is the height
		*/
		SDL_Point GetTextureSize(SDL_Texture* texture) const;

		/**
		 * @brief Draws uiobject stuff
		 * @details only text supported at the moment
		 * @param gameObject
		*/
		void DrawUI(UIObject* gameObject);

		/**
		 * @brief Draws all animation of an gameobject
		 * @param gameObject
		 * @param isUiObject
		*/
		void DrawAnimators(GameObject* gameObject, const bool isUiObject);

		/**
		 * @brief Draws animation
		 * @param gameObject GameObject of animator
		 * @param animator Defines if the object has to be drawn on world space or window space. Is false by default.
		 * @param isUiObject
		 * @param transform Contains position and rotation
		*/
		void DrawAnimator(Animator* animator, const Transform* transform, const bool isUiObject);

		/**
		 * @brief Draws text on window space
		 * @details Text is always un UI object which means its bound to windowSpace
		 * @param text The text object
		*/
		void DrawText(Text* text);

		/**
		 * @brief Wraps text in string depending on font and size of font
		 * @param pFont The font
		 * @param input The string
		 * @param width The size of the font
		*/
		void Wrap(const TTF_Font* pFont, std::string& input, const float width);

		/**
		 * @brief                           Render a multi-line text
		 * @param pFont                     The font to render the text with
		 * @param rText                     The text to render
		 * @param rTextColor                The text color
		 * @param XPosition                 The horizontal position of the text lines (defaults to 0)
		 * @param YPosition                 The vertical position of the first line of text
		 * @param Width                     The width of a textbox
		 * @param Height                    The vertical position of the first line of text
		 * @param DistanceBetweenLines      The distance between each line of text
		 * @param Align                     An enum specifying how the text has to be alligned
		*/
		void RenderMultiLineText(const TTF_Font* pFont, std::string& rText
			, const SDL_Color& rTextColor, float xPosition, float yPosition, const float width
			, const float height, const int distanceBetweenLines, const Alignment align);

		SDL_RendererFlip GetFlip(const bool flipX, const bool flipY);

		/**
		 * @brief Sets up aditional window values like name
		*/
		void UpdateWindow();
	public:
		/**
		 * Singletons should not be cloneable or assignable.
		*/
		RendererImpl(const RendererImpl& other) = delete; // copy constructor
		RendererImpl(RendererImpl&& other) noexcept = delete; // move constructor
		RendererImpl& operator=(const RendererImpl& other) = delete; // copy assignment
		RendererImpl& operator=(RendererImpl&& other) noexcept = delete;// move assignment

		/**
		 * This is the static method that controls the access to the singleton
		 * instance. On the first run, it creates a singleton object and places it
		 * into the static field. On subsequent runs, it returns the client existing
		 * object stored in the static field.
		*/

		static RendererImpl* GetInstance();

		/**
		 * Finally, any singleton should define some business logic, which can be
		 * executed on its instance.
		*/

		/**
		 * @brief Draws all related components of an gameobject
		 * @details Uses recursing
		 * @param gameObject
		 * @param isUiOject Defines if the object has to be drawn on world space or window space. Is false by default.
		*/
		void DrawGameObject(GameObject* gameObject, bool isUiOject = false);

		/**
		 * @brief Closes window
		*/
		void Exit();

		/**
		 * @brief Updates internal parameters width parameters in camera
		 * @param camera
		*/
		void UpdateCamera(Camera* camera);

		/**
		 * @brief Draws an rectangle in world space
		 * @details Rectangle is not drawn when rectangle is not in camera view.
		 * @param rect The x, y, width, height of rectangle
		 * @param angle The angle of the square
		 * @param color The color of the square
		*/
		void DrawRect(const spic::Rect& rect, const double angle, const spic::Color& color);

		/**
		 * @brief Draws an circle in world space 
					using the mid point circle algorithm https://en.wikipedia.org/w/index.php?title=Midpoint_circle_algorithm
		 * @details Circle is not drawn when circle is not in camera view.
		 * @param center The center of the circle
		 * @param angle The radius of the circle
		 * @param pixelGap The gap (in pixels) between each point in the circle
		 * @param color The color of the circle
		*/
		void DrawCircle(const spic::Point& center, const float radius, const float pixelGap, const spic::Color& color);

		/**
		 * @brief Draws a point in world space. 
		 * @details Point is not drawn when x or y are not in camera view.
		 * @param x of point
		 * @param y of point
		 * @param color The color of the point
		*/
		void DrawPoint(const spic::Point& point, const spic::Color& color);

		/**
		 * @brief Draws a point in world space
		 * @details Point is not drawn when x or y are not in camera view.
		 * @param x of point
		 * @param y of point
		*/
		void DrawPoint(const float x, const float y);

		/**
		 * @brief Draws an line in world space
		 * @details Line is not drawn when line is not in camera view.
		 * @param start The start point of an line
		 * @param end The end point of an line
		 * @param colour The colour of the line
		*/
		void DrawLine(const spic::Point& start, const spic::Point& end, const spic::Color& color);

		/**
		 * @brief Draws an ui sprite
		 * @param width The width of the ui object
		 * @param height The height of the ui object
		 * @param sprite The sprite to draw
		 * @param transform Contains position and rotation
		*/
		void DrawUISprite(const float width, const float height, const Sprite* sprite, const Transform* transform);

		/**
		 * @brief Draws an sprite
		 * @param sprite The sprite to draw
		 * @param transform Contains position and rotation
		*/
		void DrawSprite(const Sprite* sprite, const Transform* transform, bool isUiOject = false);

		/**
		 * @brief Cleans the render class before drawing it.
		*/
		void Clean();

		/**
		 * @brief Resets internal texture and font maps
		*/
		void NewScene();

		/**
		 * @brief Renders evrything in internal buffer to screen
		*/
		void Render();

		/**
		 * @brief Start up an new window
		*/
		void Start();
	};
}
#endif // RENDERERIMPL_H_