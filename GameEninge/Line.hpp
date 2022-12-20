#ifndef LINE_H_
#define LINE_H_

#include "Point.hpp"

namespace spic {
	/**
	 * @brief Line model, is used for drawing debug lines
	*/
	struct Line {
		/**
		 * @brief Start point of line
		*/
		Point start;
		/**
		 * @brief End point of line
		*/
		Point end;
	};
}

#endif // LINE_H_