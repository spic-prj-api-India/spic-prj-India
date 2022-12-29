#ifndef RENDERERGAMEOBJECTS_H_
#define RENDERERGAMEOBJECTS_H_

#include "RendererWindow.hpp"
#include "SDLPointers.hpp"
#include "GameObject.hpp"
#include "RenderText.hpp"
#include "Animator.hpp"
#include "Sprite.hpp"

/**
 * @brief The internal rendering namespace
*/
namespace spic::internal::rendering::impl
{
	/**
	 * @brief The rendering class that is in charge of rendering GameObjects and sprites
	*/
	class RendererGameObjects
	{
	private:

		std::weak_ptr<RenderTextures> textures;
		std::weak_ptr<RenderingWindow> window;
		std::weak_ptr<RenderingText> text;

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
		 * @brief Draws uiobject 
		 * @details only text supported at the moment
		 * @param gameObject The UIObject that will be drawn
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

	public:

		RendererGameObjects(std::weak_ptr<RenderTextures> textures
			, std::weak_ptr<RenderingWindow> window
			, std::weak_ptr<RenderingText> text);

		RendererGameObjects(const RendererGameObjects& other) = delete; // copy constructor
		RendererGameObjects(RendererGameObjects&& other) noexcept = delete; // move constructor
		RendererGameObjects& operator=(const RendererGameObjects& other) = delete; // copy assignment
		RendererGameObjects& operator=(RendererGameObjects&& other) noexcept = delete;// move assignment
		~RendererGameObjects() = default;

		/**
		 * @brief Draws all related components of an gameobject
		 * @details Uses recursing
		 * @param gameObject
		 * @param isUiOject Defines if the object has to be drawn on world space or window space. Is false by default.
		*/
		void DrawGameObject(GameObject* gameObject, bool isUiOject = false);

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
	};
}
#endif // RENDERERGAMEOBJECTS_H_