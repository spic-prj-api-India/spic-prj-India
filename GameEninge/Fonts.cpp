#include "Fonts.hpp"
#include <sstream>
#include <string_view>
#include <stdio.h>

namespace spic::internal::rendering {

    void Wrap(const TTF_Font* pFont, std::string& input, const size_t&& width)
    {
        std::istringstream in(input);
        std::string line;
        size_t current = 0;
        std::string word;
        std::string output = "";

        while (std::getline(in, line))
        {
            std::istringstream linein(line);
            while (linein >> word) {
                int* w = new int{ 0 };
                int* h = new int{ 0 };
                TTF_SizeUTF8((TTF_Font*)pFont, word.c_str(), w, h);
                if (current + *w + 1 > width)
                {
                    output += "\n";
                }
                output += word + ' ';
                current += *w + 1;
                delete w;
                delete h;
            }
            output += "\n";
            current = 0;
        }
        std::swap(output, input);
    }

    void RenderMultiLineText(SDL_Renderer* _render, const TTF_Font* pFont, std::string&& rText
        , const SDL_Color& rTextColor, int XPosition, int YPosition, const int Width
        , const int Height, const int DistanceBetweenLines, const Alignment Align)
    {
        // Make sure that the string contains at least 1 character
        if (!rText.empty())
        {
            Wrap(pFont, rText, Width);
            SDL_Surface* pSurface = NULL;
            SDL_Texture* pTexture = NULL;
            SDL_Rect position;

            const int   Length = rText.length();
            int         CurrentLine = 0;
            int         totalLength = 0;

            position.x = XPosition;
            position.y = YPosition;
            position.w = Width;
            position.h = Height;


            SDL_SetRenderDrawColor(_render, 255, 255, 255, 255);
            SDL_RenderDrawRect(_render, &position);

            // This string will contain one line of text
            std::string TextLine = "";

            for (int i = 0; i < Length; ++i)
            {
                // Create the text line as long as the current character is not a \n command
                if (rText[i] != '\n')
                    TextLine += rText[i];

                // Since the current character is now a \n command, it's time to create the texture containing the current text line, render it, clear the created text string and then start on a new line
                else
                {
                    if (pFont)
                        pSurface = TTF_RenderText_Solid((TTF_Font*)pFont, TextLine.c_str(), rTextColor);

                    if (pSurface)
                    {
                        pTexture = SDL_CreateTextureFromSurface(_render, pSurface);

                        if (pTexture)
                        {
                            const int TextWidth = pSurface->w;
                            const int TextHeight = pSurface->h;
                            const int nextY = YPosition + ((TextHeight + DistanceBetweenLines) * CurrentLine);

                            totalLength += nextY - YPosition + TextHeight;

                            if (totalLength > Height)
                            {
                                SDL_DestroyTexture(pTexture);
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


                            SDL_RenderCopy(_render, pTexture, NULL, &PositionQuad);

                            // Avoid memory leak
                            SDL_DestroyTexture(pTexture);
                            pTexture = NULL;
                        }

                        // Avoid memory leak
                        SDL_FreeSurface(pSurface);
                        pSurface = NULL;
                    }

                    // The current line of text has now been rendered (if the texture was successfully created and so on) and the text line string now needs to be cleared
                    TextLine = "";

                    // Time for a new line
                    ++CurrentLine;
                }
            }
        }
    }

    Fonts::Fonts()
    {
        if (TTF_Init() == -1) {
            printf("Failed to TTF: %s", SDL_GetError());
        }
    }
}

