#include "Point.hpp"
#ifndef BOUNDS_H_
#define BOUNDS_H_

namespace spic {
	class Bounds {
	public:
		Bounds();
		Bounds(const Point& v);
		Bounds(const float x, const float y, const float w, const float h);

		float Width() const;

		float Height() const;

		float Top() const;

		float Bottom() const;

		float Left() const;

		float Right() const;

		bool InBounds(Point point) const;
	private:
		float width;
		float height;
		float top;
		float bottom;
		float right;
		float left;
	};
}

#endif // BOUNDS_H_