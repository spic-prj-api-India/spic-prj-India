#include "RenderText.hpp"
#include "Debug.hpp"
#include "Defaults.hpp"
#include "InternalTime.hpp"
#include "Settings.hpp"

TTF_Font* spic::internal::rendering::impl::RenderingText::LoadFont(const std::string& font, const int size)
{
	auto key = std::make_pair(font, size);
	if (font.empty())
		return nullptr;

	bool exists = fonts.find(key) != fonts.end();
	if (exists)
		return fonts[key].get();

	auto tmp_font = FontPtr(TTF_OpenFont(font.c_str(), size));
	if (!tmp_font.get())
		return nullptr;

	fonts.emplace(key, std::move(tmp_font));

	return fonts[key].get();
}

void spic::internal::rendering::impl::RenderingText::Wrap(const TTF_Font* pFont, std::string& input, const float width)
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
	catch (const std::exception& ex)
	{
		const std::string& message = ex.what();
		spic::debug::LogError("Wrap text failed: " + message);
	}

	delete w;
	delete h;
	std::swap(output, input);
}

void spic::internal::rendering::impl::RenderingText::RenderMultiLineText(const TTF_Font* pFont, std::string& rText, const SDL_Color& rTextColor, float xPosition, float yPosition, const float width, const float height, const int distanceBetweenLines, const Alignment align)
{
	// Make sure that the string contains at least 1 character
	if (rText.empty())
		return;
	Wrap(pFont, rText, width);

	try
	{
		SurfacePtr pSurface;
		TexturePtr pTexture;

		int currentLine = 0;
		float totalLength = 0;

		// This string will contain one line of text
		std::string textLine = "";

		for (int i = 0; i < rText.length(); ++i)
		{
			// Create the text line as long as the current character is not a \n command
			if (rText.at(i) != '\n') {
				textLine += rText.at(i);
				continue;
			}

			// Since the current character is now a \n command, it's time to create the texture containing the current text line,
			// render it, clear the created text string and then start on a new line
			if (pFont)
				pSurface.reset(TTF_RenderText_Solid((TTF_Font*)pFont, textLine.c_str(), rTextColor));

			// The current line of text has now been rendered (if the texture was successfully created and so on) and the text line string now needs to be cleared
			textLine = "";

			// Time for a new line
			++currentLine;

			if (!pSurface.get())
				continue;
			pTexture.reset(SDL_CreateTextureFromSurface(this->renderer.lock().get(), pSurface.get()));

			if (pTexture.get())
			{
				const float textWidth = static_cast<float>(pSurface->w);
				const float textHeight = static_cast<float>(pSurface->h);
				const float nextY = yPosition + ((textHeight + distanceBetweenLines) * (currentLine - 1));

				totalLength = ((textHeight + distanceBetweenLines) * currentLine);

				if (totalLength > height)
				{
					pTexture.reset(NULL);
					break;
				}

				SDL_FRect PositionQuad = { 0, 0, 0, 0 };

				switch (align) {
				case Alignment::CENTER: // Position the quad centered (horizontal) in the window
					PositionQuad.x = (width / 2) - (textWidth / 2) + xPosition;
					break;
				case Alignment::RIGHT:
					PositionQuad.x = width - textWidth + xPosition;
					break;
				default: // Position the quad according to the XPosition parameter
					PositionQuad.x = xPosition;
				}

				PositionQuad.y = nextY;
				PositionQuad.w = textWidth;
				PositionQuad.h = textHeight;

				SDL_RenderCopyF(renderer.lock().get(), pTexture.get(), NULL, &PositionQuad);

				// Avoid memory leak
				pTexture.reset(NULL);
			}

			// Avoid memory leak
			pSurface.reset(NULL);
		}
	}
	catch (const std::exception& ex)
	{
		const std::string& message = ex.what();
		spic::debug::LogError("Multiline render failed: " + message);
	}
}

void spic::internal::rendering::impl::RenderingText::DrawFps()
{
	using namespace spic::internal::time;
	auto frameRate = std::to_string(static_cast<int>(std::floor(InternalTime::frameRate)));

	auto defaultText = spic::internal::defaults::TEXT_FONT;

	auto font = this->LoadFont(defaultText, 20);

	SDL_Color orange = SDL_Color{ 255,255,0,255 };
	this->RenderMultiLineText(font, frameRate, orange, static_cast<float>(spic::settings::WINDOW_WIDTH - 50), 0, 50, 100, 0, spic::Alignment::CENTER);

	if (!spic::settings::KEEP_TEXTURES_AND_FONTS_LOADED)
		this->fonts.clear();
}

void spic::internal::rendering::impl::RenderingText::Reset()
{
	//this->fonts.clear();
}

spic::internal::rendering::impl::RenderingText::RenderingText(RendererPtrWeak render) noexcept(false)
{
	if (TTF_Init() == -1) {
		printf("Failed to TTF: %s", SDL_GetError());
		exit(-1);
	}

	this->renderer = render;
}
