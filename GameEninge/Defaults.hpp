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
	inline const float PI = 3.1416f;
}

#endif // DEFAULTS_H_