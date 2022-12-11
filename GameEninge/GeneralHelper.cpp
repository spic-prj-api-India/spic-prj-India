#include "GeneralHelper.hpp"
using namespace spic;

void spic::GeneralHelper::RotatePoint(const Point& org, float angle, Point& p) noexcept
{
	p = Point{ std::cos(angle) * (p.x - org.x) - std::sin(angle) * (p.y - org.y) + org.x,
		std::sin(angle) * (p.x - org.x) + std::cos(angle) * (p.y - org.y) + org.y };
}

spic::Point spic::GeneralHelper::GetsPointY(Point& pointX, const Point& rotation, const float angle, float height, float width, float scaling) noexcept
{
	return Point{ pointX.x * scaling, pointX.y * height * scaling };
}

bool spic::GeneralHelper::SpriteSorting(const std::shared_ptr<Sprite> a, const std::shared_ptr<Sprite> b)
{
	if (a->OrderInLayer() < b->OrderInLayer())
		return true;

	if (a->OrderInLayer() > b->OrderInLayer())
		return false;

	if (a->SortingLayer() < b->SortingLayer())
		return true;

	if (a->SortingLayer() > b->SortingLayer())
		return false;

	return false;
}

std::array<Point, 4> spic::GeneralHelper::GetPoints(const Point& orgin, const float angle, const float aspectWidth, const float aspectHeight)
{
	Point center{ (orgin.x + aspectWidth) / 2, (orgin.y + aspectHeight) / 2 };

	std::array<Point, 4> returnValue = { Point{orgin}, Point{orgin.x + aspectWidth, orgin.y}, Point{orgin.x, orgin.y + aspectHeight}, Point{orgin.x + aspectWidth, orgin.y + aspectHeight} };

	for (auto value : returnValue)
	{
		RotatePoint(center, angle, value);
	}
	return returnValue;
}

bool spic::GeneralHelper::CalculateWithinSquare(const Point& point, std::array<Point, 4>& square)
{
	auto am = square[0].DotProduct(point);
	auto ab = square[0].DotProduct(square[1]);
	auto ad = square[0].DotProduct(square[4]);

	auto calc1 = am * ab;
	auto calc2 = am * ad;

	if ((0 < calc1 && calc1 * (ab * ab)) && (0 < calc2 && calc2 * (ad * ad)))
		return true;

	return false;
}

bool spic::GeneralHelper::LineIntersection(Point sPoint1, Point ePoint1, Point sPoint2, Point ePoint2, Point& intersectPoint, float& distance)
{
	float rTop = (sPoint1.y - sPoint2.y) * (ePoint2.x - sPoint2.x) - (sPoint1.x - sPoint2.x) * (ePoint2.y - sPoint2.y);
	float rePoint1ot = (ePoint1.x - sPoint1.x) * (ePoint2.y - sPoint2.y) - (ePoint1.y - sPoint1.y) * (ePoint2.x - sPoint2.x);

	float sTop = (sPoint1.y - sPoint2.y) * (ePoint1.x - sPoint1.x) - (sPoint1.x - sPoint2.x) * (ePoint1.y - sPoint1.y);
	float sePoint1ot = (ePoint1.x - sPoint1.x) * (ePoint2.y - sPoint2.y) - (ePoint1.y - sPoint1.y) * (ePoint2.x - sPoint2.x);

	if ((rePoint1ot == 0) || (sePoint1ot == 0))
	{
		//lines are parallel
		return false;
	}

	float r = rTop / rePoint1ot;
	float s = sTop / sePoint1ot;

	if ((r > 0) && (r < 1) && (s > 0) && (s < 1)) {
		distance = sPoint1.Distance(ePoint1) * r;
		intersectPoint = sPoint1 + (ePoint1 - sPoint1) * r;
		return true;
	}
	distance = 0;
	return false;
}

Point spic::GeneralHelper::GetCenter(const Point& point, const float aspectWidth, const float aspectHeight)
{
	return Point{ (point.x + aspectWidth) / 2, (point.y + aspectHeight) / 2 };
}