#ifndef PLAT_UTIL_H_
#define PLAT_UTIL_H_

#include <raylib.h>

constexpr int Sign(int x) {
	return (x > 0) - (x < 0);
}

constexpr int Sign(float x) {
	const float eps = 0.000001f;
	return (x >= eps) - (x <= -eps);
}

struct IVector2 {
	int x, y;
};

constexpr IVector2 operator+(const IVector2 &lhs, const IVector2 &rhs)
{
	return IVector2{lhs.x + rhs.x, lhs.y + rhs.y};
}

constexpr void operator+=(IVector2 &lhs, const IVector2 &rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
}

struct Aabb {
	IVector2 lo, hi;
	constexpr Aabb Translated(const IVector2 &origin);
	constexpr Rectangle AsRec(void);
};

constexpr Aabb Aabb::Translated(const IVector2 &origin)
{
	return Aabb{lo + origin, hi + origin};
}

constexpr Rectangle Aabb::AsRec(void)
{
	Rectangle result{};
	result.x = lo.x;
	result.y = lo.y;
	result.width = hi.x - lo.x + 1;
	result.height = hi.y - lo.y + 1;
	return result;
}

constexpr bool AabbsOverlap(Aabb a, Aabb b)
{
	return a.lo.x <= b.hi.x &&
		a.hi.x >= b.lo.x &&
		a.lo.y <= b.hi.y &&
		a.hi.y >= b.lo.y;
}

#endif // PLAT_UTIL_H_
