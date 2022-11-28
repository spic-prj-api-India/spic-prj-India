#include "Point.hpp"

float spic::Point::operator*(const Point& point)
{
    return this->x * point.x + this->y * point.y;
}
