#ifndef PLAT_ACTOR_H_
#define PLAT_ACTOR_H_

#include <memory>
#include <list>

#include "solid.h"
#include "util.h"

namespace Plat {

class Actor {
public:
	IVector2 position{};
	Aabb hitbox{};
	bool isRidingCurrent = false; /* flag used in Solid.Move() */

	constexpr int loX(void);
	constexpr int loY(void);
	constexpr int hiX(void);
	constexpr int hiY(void);

	bool MoveX(float amount); /* returns true if a solid was hit */
	bool MoveY(float amount); /* returns true if a solid was hit */
	bool CollideAt(const std::list<std::shared_ptr<Solid>> &solids, IVector2 position);
	constexpr Aabb GetHitboxTranslated(void);

	virtual void Update(float dt);
	virtual bool IsRiding(const Solid &solid);
	virtual void Squish(void);
private:
	float xRemainder = 0.0f, yRemainder = 0.0f;
};

constexpr Aabb Actor::GetHitboxTranslated(void)
{
	return hitbox.Translated(position);
}

constexpr int Actor::loX(void)
{
	return GetHitboxTranslated().lo.x;
}

constexpr int Actor::loY(void)
{
	return GetHitboxTranslated().lo.y;
}

constexpr int Actor::hiX(void)
{
	return GetHitboxTranslated().hi.x;
}

constexpr int Actor::hiY(void)
{
	return GetHitboxTranslated().hi.y;
}

} // namespace Plat

#endif // PLAT_ACTOR_H_
