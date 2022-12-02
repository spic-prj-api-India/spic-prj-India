#ifndef TEXT_H_
#define TEXT_H_

#include "UIObject.hpp"
#include "Color.hpp"
#include <string>

namespace spic {

    /**
     * @brief Enumeration for different text alignments.
     * @spicapi
     */
    enum class Alignment {
        LEFT,
        CENTER,
        RIGHT,
    };

    /**
     * @brief Class representing a piece of text which can be rendered.
     * @spicapi
     */
    class Text : public UIObject {
        public:
            Text();

            /**
             * @brief The text's constructor
             * @param width Width of UIObject.
             * @param height Height of UIObject.
             * @param text Displayed text.
             * @param font Font of text.
             * @param size Font size of text.
             * @param alignment Alignment of text.
             * @param color Color of text.
             * @spicapi
             */
            Text(const float width, const float height
                , const std::string& text = ""
                , const std::string& font = ""
                , const int size = 20
                , const Alignment alignment = Alignment::CENTER
                , const Color& color = Color::black());

            /**
             * @brief Gets display text of Text.
             * @return string.
             * @spicapi
            */
            const std::string _Text();
            
            /**
            * @brief Sets display text of Text.
            * @param text Desired value.
            * @spicapi
            */
            const void _Text(const std::string& text);

            /**
             * @brief Gets font of Text.
             * @return string.
             * @spicapi
            */
            const std::string Font();

            /**
            * @brief Sets font of Text.
            * @param font Desired value.
            * @spicapi
            */
            const void Font(const std::string& font);

            /**
             * @brief Gets font size of Text.
             * @return int.
             * @spicapi
            */
            const int Size();

            /**
            * @brief Sets font size of Text.
            * @param size Desired value.
            * @spicapi
            */
            const void Size(const int size);

            /**
             * @brief Gets alignment of Text.
             * @return spic::Alignment.
             * @spicapi
            */
            const spic::Alignment Alignment();

            /**
            * @brief Sets alignment of Text (LEFT, CENTER, RIGHT).
            * @param text Desired value.
            * @spicapi
            */
            const void Alignment(const spic::Alignment alignment);

            /**
             * @brief Gets color of Text.
             * @return spic::Color.
             * @spicapi
            */
            const spic::Color Color();

            /**
            * @brief Sets color of Text.
            * @param color Desired value.
            * @spicapi
            */
            const void Color(const spic::Color color);
        private:
            std::string text;
            std::string font;
            int size;
            spic::Alignment alignment;
            spic::Color color;
    };

}

#endif // TEXT_H_
