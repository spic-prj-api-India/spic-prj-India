#ifndef RENDERERTEXT_H_
#define RENDERERTEXT_H_

#include "SDLPointers.hpp"
#include <string>
#include <map>
#include "Text.hpp"

namespace spic::internal::rendering::impl
{
	/**
	 * @brief Class that renders all text related stuff
	*/
	class RenderingText
	{
	private:

		/**
		 * @brief Font Map
		*/
		std::map<std::pair<std::string, int>, FontPtr> fonts;

		/**
		 * @brief sdl renderer ptr
		*/
		RendererPtrWeak renderer;

	private:
		/**
		 * @brief Wraps text in string depending on font and size of font
		 * @param pFont The font
		 * @param input The string
		 * @param width The size of the font
		*/
		void Wrap(const TTF_Font* pFont, std::string& input, const float width);

	public:

		/**
		 * @brief Constructor
		 * @param render A reference to the current renderer ptr
		*/
		RenderingText(RendererPtrWeak render) noexcept(false);

		/**
		 * @brief A font file
		 * @param font font The font name
		 * @param size The size of the font
		 * @return A TTF_Font pointer which is managed in a RAI object in this class
		*/
		TTF_Font* LoadFont(const std::string& font, const int size);

		/**
		 * @brief                           Render a multi-line text
		 * @param pFont                     The font to render the text with
		 * @param rText                     The text to render
		 * @param rTextColor                The text color
		 * @param xPosition                 The horizontal position of the text lines (defaults to 0)
		 * @param yPosition                 The vertical position of the first line of text
		 * @param width                     The width of a textbox
		 * @param height                    The vertical position of the first line of text
		 * @param distanceBetweenLines      The distance between each line of text
		 * @param align                     An enum specifying how the text has to be alligned
		*/
		void RenderMultiLineText(const TTF_Font* pFont, std::string& rText
			, const SDL_Color& rTextColor, float xPosition, float yPosition, const float width
			, const float height, const int distanceBetweenLines, const Alignment align);

		/**
		 * @brief Renders the fps counter
		*/
		void DrawFps();

		/**
		 * @brief Resets the fonts map
		*/
		void Reset();
	};
}
#endif //RENDERERTEXT_H_