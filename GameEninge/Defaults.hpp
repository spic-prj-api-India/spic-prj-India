#ifndef DEFAULTS_H_
#define DEFAULTS_H_

#include <string>

namespace spic::internal::Defaults {
	/**
	 * @brief Default button texture
	*/
	inline std::string BUTTON_TEXTURE = "defaults/textures/UISprite.png";

	/**
	 * @brief Default font text
	*/
	inline std::string TEXT_FONT = "defaults/fonts/07558_CenturyGothic.ttf";

	/**
	 * @brief Default missing texture
	*/
	inline std::string MISSING_TEXTURE = "defaults/textures/missing_texture.png";

	/**
	 * @brief Default rect texture
	*/
	const inline std::string RECT_TEXTURE = "defaults/textures/Rectangle.png";

	/*
	* @brief Definition of PI
	*/
	inline constexpr float PI = 3.141592653589793238462643383279502884f;

	/*
	* @brief Definition of half PI
	*/
	inline constexpr float HALF_PI = PI / 2.0f;
}

#endif // DEFAULTS_H_