#include "GeneralHelper.hpp"
#include <random>

using namespace spic;

void spic::generalHelper::RotatePoint(const Point& org, float angle, Point& p) noexcept
{
	p = Point{ std::cos(angle) * (p.x - org.x) - std::sin(angle) * (p.y - org.y) + org.x,
		std::sin(angle) * (p.x - org.x) + std::cos(angle) * (p.y - org.y) + org.y };
}

spic::Point spic::generalHelper::GetsPointY(Point& pointX, const Point& rotation, const float angle, float height, float width, float scaling) noexcept
{
	return Point{ pointX.x * scaling, pointX.y * height * scaling };
}

std::string spic::generalHelper::GetRandomUUID()
{
	static std::random_device dev;
	static std::mt19937 rng(dev());

	std::uniform_int_distribution<int> dist(0, 15);

	const char* v = "0123456789abcdef";
	const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

	std::string res;
	for (int i = 0; i < 16; i++) {
		if (dash[i]) res += "-";
		res += v[dist(rng)];
		res += v[dist(rng)];
	}
	return res;
}

bool spic::generalHelper::SpriteSorting(const std::shared_ptr<Sprite> a, const std::shared_ptr<Sprite> b)
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

bool spic::generalHelper::NetworkPacketSorting(const NetworkPacket& a, const NetworkPacket& b)
{
	if (a.timeSpan < b.timeSpan)
		return true;

	return false;
}

std::array<Point, 4> spic::generalHelper::GetPoints(const Point& orgin, const float angle, const float aspectWidth, const float aspectHeight)
{
	Point center{ (orgin.x + aspectWidth) / 2, (orgin.y + aspectHeight) / 2 };

	std::array<Point, 4> returnValue = { Point{orgin}, Point{orgin.x + aspectWidth, orgin.y}, Point{orgin.x, orgin.y + aspectHeight}, Point{orgin.x + aspectWidth, orgin.y + aspectHeight} };

	for (auto value : returnValue)
	{
		RotatePoint(center, angle, value);
	}
	return returnValue;
}



bool spic::generalHelper::CalculateWithinSquare(const Point& point, std::array<Point, 4>& square)
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

bool ValueInRange(float value, float min, float max)
{
	return (value >= min) && (value <= max);
}

bool spic::generalHelper::RectIntersection(const Rect& rect1, const Rect& rect2) {
	const bool xOverlap = ValueInRange(rect1.x, rect2.x, rect2.x + rect2.w) ||
		ValueInRange(rect2.x, rect1.x, rect1.x + rect1.w);

	const bool yOverlap = ValueInRange(rect1.y, rect2.y, rect2.y + rect2.h) ||
		ValueInRange(rect2.y, rect1.y, rect1.y + rect1.h);

	return xOverlap && yOverlap;
}

bool spic::generalHelper::LineIntersection(Point sPoint1, Point ePoint1, const Point& sPoint2, const Point& ePoint2, Point& intersectPoint, float& distance)
{
	const float rTop = (sPoint1.y - sPoint2.y) * (ePoint2.x - sPoint2.x) - (sPoint1.x - sPoint2.x) * (ePoint2.y - sPoint2.y);
	const float rePoint1ot = (ePoint1.x - sPoint1.x) * (ePoint2.y - sPoint2.y) - (ePoint1.y - sPoint1.y) * (ePoint2.x - sPoint2.x);

	const float sTop = (sPoint1.y - sPoint2.y) * (ePoint1.x - sPoint1.x) - (sPoint1.x - sPoint2.x) * (ePoint1.y - sPoint1.y);
	const float sePoint1ot = (ePoint1.x - sPoint1.x) * (ePoint2.y - sPoint2.y) - (ePoint1.y - sPoint1.y) * (ePoint2.x - sPoint2.x);

	if ((rePoint1ot == 0) || (sePoint1ot == 0))
	{
		//lines are parallel
		return false;
	}

	const float r = rTop / rePoint1ot;
	const float s = sTop / sePoint1ot;

	if ((r > 0) && (r < 1) && (s > 0) && (s < 1)) {
		distance = sPoint1.Distance(ePoint1) * r;
		intersectPoint = sPoint1 + (ePoint1 - sPoint1) * r;
		return true;
	}
	distance = 0;
	return false;
}

Point spic::generalHelper::GetCenter(const Point& point, const float aspectWidth, const float aspectHeight)
{
	return Point{ (point.x + aspectWidth) / 2, (point.y + aspectHeight) / 2 };
}