#include "GeneralHelper.hpp"
#include <random>

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

std::string spic::GeneralHelper::GetRandomUUID()
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

bool spic::GeneralHelper::NetworkPacketSorting(const NetworkPacket& a, const NetworkPacket& b)
{
	if (a.timeSpan < b.timeSpan)
		return true;

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
	auto am = (square[0] * point);
	auto ab = (square[0] * square[1]);
	auto ad = (square[0] * square[4]);

	auto calc1 = am * ab;
	auto calc2 = am * ad;

	if ((0 < calc1 && calc1 * (ab * ab)) && (0 < calc2 && calc2 * (ad * ad)))
		return true;

	return false;
}
Point spic::GeneralHelper::GetCenter(const Point& point, const float aspectWidth, const float aspectHeight)
{
	return Point{ (point.x + aspectWidth) / 2, (point.y + aspectHeight) / 2 };
}