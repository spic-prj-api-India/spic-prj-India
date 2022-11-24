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
        left,
        center,
        right
    };

    /**
     * @brief Class representing a piece of text which can be rendered.
     * @spicapi
     */
    class Text : public UIObject {
        public:
            Text();
            Text( const std::string& text
                , const std::string& font
                , const int size
                , const spic::Alignment alignment
                , const spic::Color& color);

            const std::string _Text();
            const void _Text(const std::string& text);

            const std::string Font();
            const void Font(const std::string& font);

            const int Size();
            const void Size(const int size);

            const spic::Alignment Alignment();
            const void Alignment(const spic::Alignment alignment);

            const spic::Color Color();
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
