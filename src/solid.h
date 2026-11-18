#ifndef PLAT_SOLID_H_
#define PLAT_SOLID_H_

#include "util.h"

namespace Plat {

class Solid {
public:
	IVector2 position{};
	Aabb hitbox{};
	bool isCollidable = 1;

	constexpr int loX(void);
	constexpr int loY(void);
	constexpr int hiX(void);
	constexpr int hiY(void);

	constexpr Aabb GetHitboxTranslated(void);
	void Move(float x, float y);
private:
	float xRemainder = 0.0f, yRemainder = 0.0f;
};

constexpr Aabb Solid::GetHitboxTranslated(void)
{
	return hitbox.Translated(position);
}

constexpr int Solid::loX(void)
{
	return GetHitboxTranslated().lo.x;
}

constexpr int Solid::loY(void)
{
	return GetHitboxTranslated().lo.y;
}

constexpr int Solid::hiX(void)
{
	return GetHitboxTranslated().hi.x;
}

constexpr int Solid::hiY(void)
{
	return GetHitboxTranslated().hi.y;
}

} // namespace Plat

#endif // PLAT_SOLID_H_
