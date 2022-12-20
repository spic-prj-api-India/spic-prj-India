#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Point.hpp"

namespace spic {
	/**
	 * @brief Circle model, is used for drawing debug circles
	*/
	struct Circle {
		Point center;
		float radius;
	};
}

#endif // CIRCLE_H_