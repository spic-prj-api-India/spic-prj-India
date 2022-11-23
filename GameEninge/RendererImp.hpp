#ifndef RENDERER_H_
#define RENDERER_H_

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
#include "WindowValues.hpp"

#define SCREEN_WIDTH_DEFAULT 1200
#define SCREEN_HEIGHT_DEFAULT 800
#undef main

/// @brief The internal audio namespace wich contains all audio related content
namespace spic::internal::rendering {

    struct SDL_Deleter {
        void operator()(SDL_Surface* ptr) { if (ptr) SDL_FreeSurface(ptr); }
        void operator()(SDL_Texture* ptr) { if (ptr) SDL_DestroyTexture(ptr); }
        void operator()(SDL_Renderer* ptr) { if (ptr) SDL_DestroyRenderer(ptr); }
        void operator()(SDL_Window* ptr) { if (ptr) SDL_DestroyWindow(ptr); }
        void operator()(SDL_RWops* ptr) { if (ptr) SDL_RWclose(ptr); }
        void operator()(TTF_Font* ptr) { if (ptr) TTF_CloseFont(ptr); }
    };

    using SurfacePtr = std::unique_ptr<SDL_Surface, SDL_Deleter>;
    using TexturePtr = std::unique_ptr<SDL_Texture, SDL_Deleter>;
    using RendererPtr = std::unique_ptr<SDL_Renderer, SDL_Deleter>;
    using WindowPtr = std::unique_ptr<SDL_Window, SDL_Deleter>;
    using RWopsPtr = std::unique_ptr<SDL_RWops, SDL_Deleter>;
    using FontPtr = std::unique_ptr<TTF_Font, SDL_Deleter>;

    class RendererImp
    {
        /**
        * The Singleton's constructor/destructor should always be private to
        * prevent direct construction/desctruction calls with the `new`/`delete`
        * operator.
        */
    private:
        static RendererImp* pinstance_;
        static std::mutex mutex_;
       
        double lastTick;
        double deltatime;

        SDL_Rect camera;
        float scaling;
        float rotation;
        Color backgroundColor;
        float aspectHeight;
        float aspectWidth;

        WindowPtr window;
        RendererPtr renderer;
        
        std::map<std::string, TexturePtr> textures;
        std::map<std::string, FontPtr> fonts;

        SDL_Rect windowCamera;

        /// @brief Mutex for making the private instance of this class thread safe
        std::mutex mutex_rendering;

        
    protected:
        RendererImp() noexcept(false);
        ~RendererImp();

    
        void DrawSprites(GameObject* gameObject, const bool isUiObject);
        SDL_Texture* LoadTexture(Sprite* sprite);
        TTF_Font* LoadFont(const std::string& font, const int size);

        SDL_Point GetTextureSize(SDL_Texture* texture);

        void DrawUIText(GameObject* gameObject);
        void DrawAnimators(GameObject* gameObject, const bool isUiObject);
        void DrawAnimator(Animator* sprite, const bool isUiObject, const Transform* transform);
        void DrawSprite(Sprite* sprite, const bool isUiObject, const Transform* transform);
        void DrawGameObject(GameObject* gameObject, bool isUiOject = false);

        void Wrap(const TTF_Font* pFont, std::string& input, const size_t&& width);

        /**
        * Render a multi-line text
        * \param _render                The sdl2 renderer class
        * \param pFont                  The font to render the text with
        * \param rText                  The text to render
        * \param rTextColor             The text color
        * \param XPosition              The horizontal position of the text lines (defaults to 0)
        * \param YPosition              The vertical position of the first line of text
        * \param Width                  The width of a textbox
        * \param Height                 The vertical position of the first line of text
        * \param DistanceBetweenLines   The distance between each line of text
        * \param CenteredInWindow       A bool specifying if the text lines should be centered (horizontal) in the window or not (defaults to true)

        * \note                         Create a new line by inserting the \n command in the string. The string needs to end with a \n command for the last line of text to be rendered
        */
        void RenderMultiLineText(SDL_Renderer* _render, const TTF_Font* pFont, std::string& rText
            , const SDL_Color& rTextColor, int XPosition, int YPosition, const int Width
            , const int Height, const int DistanceBetweenLines, const Alignment Align = Alignment::left);

        
        
        
    public:
        /**
            * Singletons should not be cloneable or assignable.
            */
        RendererImp(const RendererImp& other) = delete; // copy constructor
        RendererImp(RendererImp&& other) noexcept = delete; // move constructor
        RendererImp& operator=(const RendererImp& other) = delete; // copy assignment
        RendererImp& operator=(RendererImp&& other) noexcept = delete;// move assignment


        /**
            * This is the static method that controls the access to the singleton
            * instance. On the first run, it creates a singleton object and places it
            * into the static field. On subsequent runs, it returns the client existing
            * object stored in the static field.
            */

        static RendererImp* GetInstance();

        /**
            * Finally, any singleton should define some business logic, which can be
            * executed on its instance.
            */

        void Draw(GameObject* gameObject);

        void UpdateWindow(const spic::window::WindowValues* values);
        void UpdateCamera(Camera* camera);

        void SetBackgroundColor();
        void DrawLine(const Point* start, const Point* end, const Color* colour);
        void DrawSprite(const Transform* position, Sprite* sprite);
        void DrawAnimator(const Transform* position, Animator* animator);
        void DrawText(Text* text);
        void Clean();
        void NewScene();
        void Render();

        void Start(const spic::window::WindowValues* values);
        void Exit();
        
    };
}
#endif // AUDIOMANAGER_H_