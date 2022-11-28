#include "RendererImpl.hpp"
#include "UIObject.hpp"
#include <algorithm>
#include "Text.hpp"
#include "Animator.hpp"
#include "GeneralHelper.hpp"
#include <sstream>
#include <string_view>
#include <stdio.h>
#include <filesystem>
using namespace spic;
using namespace spic::window;
using namespace spic::internal::rendering;
using namespace spic::GeneralHelper;
#define UINT_8_BEGIN 0
#define UINT_8_END 255

RendererImpl* RendererImpl::pinstance_{ nullptr };
std::mutex RendererImpl::mutex_;

RendererImpl::RendererImpl() noexcept(false) : camera{ 0, 0, 0, 0 }, backgroundColor {0,0,0,1}, scaling{1}, rotation{0}
{
}

RendererImpl::~RendererImpl()
{
    try
    {
        Exit();
    }
    catch (...)
    {

    }
}

void RendererImpl::Start(const spic::window::WindowValues* values)
{
    Exit(); // does nothing if it has not been called yet

    // sets up video
    if (SDL_Init(SDL_INIT_VIDEO != 0))
    {
        std::cout << SDL_GetError() << std::endl;
        exit(-1);
    }

    // for deltatime 
    lastTick = SDL_GetTicks();
    deltatime = 0;

    // TODO: Zet in CreateWindow
    const SDL_WindowFlags w_flags = (SDL_WindowFlags)(SDL_WINDOW_ALLOW_HIGHDPI);
    window = WindowPtr(SDL_CreateWindow(values->WindowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, values->ScreenWidth, values->ScreenHeight, w_flags));
    if (window.get() == nullptr) {
        std::cerr << SDL_GetError() << std::endl;
        exit(-1);
    }

    SDL_SetWindowAlwaysOnTop(window.get(),
        (SDL_bool)values->SetOnTop);

    // TODO: Zet in CreateRenderer
    SDL_RendererFlags rendererFlags = (SDL_RendererFlags)(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    renderer = RendererPtr(SDL_CreateRenderer(window.get(), -1, rendererFlags));
    if (renderer.get() == nullptr) {
        std::cerr << SDL_GetError() << std::endl;
        exit(-1);
    }

    //TODO: Zet in CreateTTF
    if (TTF_Init() == -1) {
        printf("Failed to TTF: %s", SDL_GetError());
        exit(-1);
    }

    this->UpdateWindow(values);


    auto tmp_sprites = SurfacePtr(IMG_Load("assets/textures/missing_texture.png"));
    if (!tmp_sprites.get())
        return;

    missingTexture = TexturePtr(SDL_CreateTextureFromSurface(renderer.get(), tmp_sprites.get()));
}

void RendererImpl::Exit()
{
    renderer.release();
    window.release();
    SDL_Quit();
}

SDL_Point RendererImpl::GetTextureSize(SDL_Texture* texture) const
{
    SDL_Point size;
    SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
    return size;
}

void RendererImpl::DrawSprites(GameObject* gameObject, const bool isUiObject)
{
    const auto transform = gameObject->Transform();
    auto _sprites = gameObject->GetComponents<Sprite>();
    std::sort(_sprites.begin(), _sprites.end(), spic::GeneralHelper::SpriteSorting);
    for (auto& sprite : _sprites)
    {
        DrawSprite(sprite.get(), isUiObject, transform.get());
    }
}

SDL_Texture* RendererImpl::LoadTexture(const Sprite* sprite)
{
    if (sprite->_Sprite().empty())
        return missingTexture.get();
    bool exists = textures.find(sprite->_Sprite()) != textures.end();
    if (exists)
        return textures[sprite->_Sprite()].get();

    auto tmp_sprites = SurfacePtr(IMG_Load(sprite->_Sprite().c_str()));
    if (!tmp_sprites.get())
        return missingTexture.get();

    auto texture = TexturePtr(SDL_CreateTextureFromSurface(renderer.get(), tmp_sprites.get()));
    auto returnPntr = texture.get();
    textures.emplace(sprite->_Sprite(), std::move(texture));
    return returnPntr;
}

TTF_Font* RendererImpl::LoadFont(const std::string& font, const int size)
{
    if (font.empty())
        return nullptr;
    bool exists = fonts.find(font) != fonts.end();
    if (exists)
        return fonts[font].get();

    auto tmp_font = FontPtr(TTF_OpenFont(font.c_str(), size));
    if (!tmp_font.get())
        return nullptr;

    return tmp_font.get();
}


void RendererImpl::DrawUI(UIObject* gameObject)
{
    auto* castedUiObject = dynamic_cast<Text*>(gameObject);
    const bool thisIsTextObject = castedUiObject != nullptr;
    if (thisIsTextObject)
        DrawText(castedUiObject);
}

void RendererImpl::NewScene()
{
    textures.clear();
    fonts.clear();
}

void RendererImpl::DrawAnimators(GameObject* gameObject, const bool isUiObject)
{
    auto _animator = gameObject->GetComponents<Animator>();
    

    for (auto& animator : _animator)
    {
        DrawAnimator(animator.get(), isUiObject, gameObject->Transform().get());       
    }
}

void RendererImpl::DrawAnimator(Animator* animator, const bool isUiObject, const Transform* position)
{

    auto sprites = animator->Sprites();
    // sort sprites

    const auto framesAmount = sprites.back()->OrderInLayer();

    const int fps = 1000;

    //const auto frame = static_cast<uint64_t>(SDL_GetTicks() / ((static_cast<double>(fps) / animator->Fps()) * Time::TimeScale())) % framesAmount;

    const auto frame = static_cast<uint64_t>(SDL_GetTicks() / (1000 /animator->Fps() * Time::TimeScale())) % framesAmount;

    for (auto& sprite : sprites)
    {
        if (sprite->OrderInLayer() == frame && !animator->IsFozen())
        {
            //animator->Index(frame);
            DrawSprite(sprite.get(), isUiObject, position);
        }
            
        else if (sprite->OrderInLayer() == animator->Index() && animator->IsFozen())
            DrawSprite(sprite.get(), isUiObject, position);
    }

}

void RendererImpl::SetBackgroundColor()
{
    SDL_SetRenderDrawColor(renderer.get()
        , std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.R()))
        , std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.G()))
        , std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.B()))
        , std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.A()))
    );

    SDL_RenderFillRect(renderer.get(), &this->windowCamera);
}

RendererImpl* RendererImpl::GetInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new RendererImpl();
    }
    return pinstance_;
}

void RendererImpl::DrawGameObject(GameObject* gameObject, bool isUiOject)
{   
    if (gameObject->Active())
    {
        auto* castedUiObject = dynamic_cast<UIObject*>(gameObject);
        const bool thisIsUIObject = castedUiObject != nullptr;


        if (!isUiOject && thisIsUIObject)
        {
            isUiOject = thisIsUIObject;
        }

        DrawSprites(gameObject, isUiOject);

        DrawAnimators(gameObject,isUiOject);

        for (auto& child : gameObject->GetChildren())
        {
            DrawGameObject(child.get(), isUiOject);
        }

        if(isUiOject)
            DrawUI(castedUiObject);
    }
}

void RendererImpl::DrawLine(const Point* start, const Point* end, const Color* colour)
{
    SDL_SetRenderDrawColor(renderer.get()
        , std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, colour->R()))
        , std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, colour->G()))
        , std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, colour->B()))
        , std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, colour->A())));
    SDL_RenderDrawLine(renderer.get()
        , std::lround(start->x)
        , std::lround(start->y)
        , std::lround(end->x)
        , std::lround(end->y));
}


void RendererImpl::DrawText(Text* text)
{
    if (std::filesystem::exists(text->Font().c_str()))
    {
        auto font = TTF_OpenFont(text->Font().c_str(), text->Size());
        auto transform = text->Transform().get();
        auto colour = SDL_Color{ static_cast<unsigned char>(std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, text->Color().R())))
            , static_cast<unsigned char>(std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, text->Color().G())))
            , static_cast<unsigned char>(std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, text->Color().B()))) };
        std::string texts{ text->_Text() };
        text->Alignment();

        this->RenderMultiLineText(font, texts, colour, std::lround(transform->position.x), std::lround(transform->position.y), std::lround(text->Width()), std::lround(text->Height()), 2, text->Alignment());

        TTF_CloseFont(font);
    }
}

void RendererImpl::DrawSprite(const Sprite* sprite, const bool isUiObject, const Transform* transform)
{
    if (transform == nullptr)
        return;

    SDL_Texture* texture = LoadTexture(sprite);
    auto textureSize = GetTextureSize(texture);

    const int width = (sprite->Width() == 0) ? textureSize.x : sprite->Width();
    const int height = (sprite->Height() == 0) ? textureSize.y : sprite->Height();
    SDL_Rect dstRect = { std::lround(transform->position.x)
        , std::lround(transform->position.y)
        , std::lround(width * transform->scale * this->scaling)
        , std::lround(height * transform->scale * this->scaling) };

    
    SDL_Rect sourceRect = { std::lround(sprite->X())
        , std::lround(sprite->Y())
        , std::lround(width)
        , std::lround(height) };


    if (SDL_HasIntersection(&dstRect, &this->camera) && !isUiObject)
    {
        dstRect = { dstRect.x - this->camera.x
            , dstRect.y - this->camera.y
            , dstRect.w
            , dstRect.h };
    }
    else if (!isUiObject)
        return;

    else if (!SDL_HasIntersection(&dstRect, &this->windowCamera))
        return;

    const auto color = sprite->Color();

    SDL_SetTextureColorMod(texture
        , std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, color.R()))
        , std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, color.G()))
        , std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, color.B())));

    SDL_SetTextureAlphaMod(texture,
        std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, color.A())));

    auto center = SDL_Point{ std::lround(dstRect.x + (dstRect.w/2))
        ,std::lround(dstRect.y + (dstRect.h / 2)) };
    
    SDL_RendererFlip flip; 
    
    if (sprite->FlipX() && sprite->FlipY())
        flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    else if (sprite->FlipX())
        flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL);
    else if (sprite->FlipX())
        flip = (SDL_RendererFlip)(SDL_FLIP_VERTICAL);
    else
        flip = (SDL_RendererFlip)(SDL_FLIP_NONE);

    if (texture == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        SDL_RenderCopyEx(renderer.get(), NULL, &sourceRect, &dstRect, transform->rotation, &center, flip);
        return;
    }

    SDL_RenderCopyEx(renderer.get(), texture, &sourceRect, &dstRect, transform->rotation, &center, flip);
}

void RendererImpl::UpdateCamera(Camera* camera)
{
    auto transform = camera->Transform().get();
    const auto pos = transform->position;
    this->scaling = transform->scale;
    this->rotation = transform->rotation;

    int width, height = 0;
    SDL_GetWindowSize(window.get(), &width, &height);
    this->camera = 
        { std::lround(pos.x)
        , std::lround(pos.y)
        , width
        , height };

    this->backgroundColor = camera->BackgroundColor();
}

void RendererImpl::Clean()
{
    SDL_RenderClear(renderer.get());
    SDL_SetRenderDrawColor(renderer.get()
        , std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.R()))
        , std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.G()))
        , std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.B()))
        , std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.A()))
    );
}

void RendererImpl::Render()
{
    SDL_SetRenderDrawColor(renderer.get()
        , std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.R()))
        , std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.G()))
        , std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.B()))
        , std::lround(std::lerp(UINT_8_BEGIN, UINT_8_END, this->backgroundColor.A()))
    );

    SDL_RenderPresent(renderer.get());
}

void RendererImpl::UpdateWindow(const spic::window::WindowValues* values)
{
    Uint32 window_flags = -1;

    switch (values->selector)
    {
    case FULLSCREENTYPE::BORDERLESS:
        window_flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
        break;
    case FULLSCREENTYPE::FULLSCREEN:
        window_flags = SDL_WINDOW_FULLSCREEN;
        break;
    case FULLSCREENTYPE::WINDOWED:
        window_flags = 0;
        break;
    }

    if (window_flags != -1)
        SDL_SetWindowFullscreen(window.get(),
            window_flags);

    int width, height = 0;
    SDL_GetWindowSize(window.get(), &width, &height);
    this->windowCamera = { 0, 0, width, height };
    this->camera.w = width;
    this->camera.h = height;
}


void RendererImpl::Wrap(const TTF_Font* pFont, std::string& input, const size_t&& width)
{
    std::istringstream in(input);
    std::string line;
    size_t current = 0;
    std::string word;
    std::string output = "";

    int* w = new int{ 0 };
    int* h = new int{ 0 };

    try
    {
        while (std::getline(in, line))
        {
            std::istringstream linein(line);
            while (linein >> word) {
                *w = 0;
                *h = 0;
                TTF_SizeUTF8((TTF_Font*)pFont, word.c_str(), w, h);
                if (current + *w + 1 > width)
                {
                    output += "\n";
                }
                output += word + ' ';
                current += *w + 1;
            }
            output += "\n";
            current = 0;
        }
    }
    catch (...)
    {

    }

    delete w;
    delete h;
    std::swap(output, input);
}

void RendererImpl::RenderMultiLineText(const TTF_Font* pFont, std::string& rText
    , const SDL_Color& rTextColor, int XPosition, int YPosition, const int Width
    , const int Height, const int DistanceBetweenLines, const Alignment Align)
{   
    // Make sure that the string contains at least 1 character
    if (!rText.empty())
    {
        Wrap(pFont, rText, Width);
        try
        {

            SurfacePtr pSurface;
            TexturePtr pTexture;

            int         CurrentLine = 0;
            int         totalLength = 0;

            // This string will contain one line of text
            std::string TextLine = "";

            for (int i = 0; i < rText.length(); ++i)
            {
                // Create the text line as long as the current character is not a \n command
                if (rText[i] != '\n')
                    TextLine += rText[i];

                // Since the current character is now a \n command, it's time to create the texture containing the current text line, render it, clear the created text string and then start on a new line
                else
                {
                    if (pFont)
                        pSurface.reset(TTF_RenderText_Solid((TTF_Font*)pFont, TextLine.c_str(), rTextColor));

                    if (pSurface.get())
                    {
                        pTexture.reset(SDL_CreateTextureFromSurface(this->renderer.get(), pSurface.get()));

                        if (pTexture.get())
                        {
                            const int TextWidth = pSurface->w;
                            const int TextHeight = pSurface->h;
                            const int nextY = YPosition + ((TextHeight + DistanceBetweenLines) * CurrentLine);

                            totalLength += nextY - YPosition;

                            if (totalLength > Height)
                            {
                                pTexture.reset(NULL);
                                break;
                            }

                            SDL_Rect PositionQuad = { 0, 0, 0, 0 };

                            switch (Align) {
                            case Alignment::center: // Position the quad centered (horizontal) in the window
                                PositionQuad.x = (Width / 2) - (TextWidth / 2) + XPosition;
                                break;
                            case Alignment::right:
                                PositionQuad.x = Width - TextWidth + XPosition;
                                break;

                            default: // Position the quad according to the XPosition parameter
                                PositionQuad.x = XPosition;
                            }

                            PositionQuad.y = nextY;
                            PositionQuad.w = TextWidth;
                            PositionQuad.h = TextHeight;


                            SDL_RenderCopy(this->renderer.get(), pTexture.get(), NULL, &PositionQuad);

                            // Avoid memory leak
                            pTexture.reset(NULL);
                        }

                        // Avoid memory leak
                        pSurface.reset(NULL);
                    }

                    // The current line of text has now been rendered (if the texture was successfully created and so on) and the text line string now needs to be cleared
                    TextLine = "";

                    // Time for a new line
                    ++CurrentLine;
                }
            }
        }
        catch (...)
        {
            return;
        }
        
    }
}