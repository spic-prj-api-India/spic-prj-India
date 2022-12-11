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

	/*
	* @brief Definition of PI
	*/
	inline const float PI = 3.141592653589793238462643383279502884f;

	/*
	* @brief Definition of half PI
	*/
	inline const float HALF_PI = PI / 2.0f;
}

#endif // DEFAULTS_H_