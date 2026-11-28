#ifndef PLAT_SOLID_H_
#define PLAT_SOLID_H_

#include "util.h"

namespace Plat {

class Solid {
public:
	IVector2 position{};
	Aabb hitbox{};
	bool isCollidable = 1;

	constexpr int loX(void) const;
	constexpr int loY(void) const;
	constexpr int hiX(void) const;
	constexpr int hiY(void) const;
	constexpr bool ShouldDelete(void); /* tells the game loop to delete the object */
	constexpr void DeleteSelf(void); /* sets the object up for deletion */

	constexpr Aabb GetHitboxTranslated(void) const;
	void Move(float x, float y);

	virtual void Update(float dt);
private:
	bool shouldDelete = false;
	float xRemainder = 0.0f, yRemainder = 0.0f;
};

constexpr bool Solid::ShouldDelete(void)
{
	return shouldDelete;
}

constexpr void Solid::DeleteSelf(void)
{
	shouldDelete = true;
}

constexpr Aabb Solid::GetHitboxTranslated(void) const
{
	return hitbox.Translated(position);
}

constexpr int Solid::loX(void) const
{
	return GetHitboxTranslated().lo.x;
}

constexpr int Solid::loY(void) const
{
	return GetHitboxTranslated().lo.y;
}

constexpr int Solid::hiX(void) const
{
	return GetHitboxTranslated().hi.x;
}

constexpr int Solid::hiY(void) const
{
	return GetHitboxTranslated().hi.y;
}

} // namespace Plat

#endif // PLAT_SOLID_H_
