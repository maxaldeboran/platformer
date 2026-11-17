#include "actor.h"

#include <cmath>

#include "globals.h"

namespace Plat {

/* default virtual method impl */
bool Actor::IsRiding(const Solid &solid)
{
	(void)solid;
	return false;
}

/* default virtual method impl */
void Actor::Squish(void)
{
	TraceLog(LOG_INFO, "Squish!");
}

bool Actor::CollideAt(const std::vector<Solid> &solids, IVector2 position)
{
	Aabb box = hitbox.Translated(position);

	for (auto solid : solids) {
		Aabb other = solid.GetHitboxTranslated();

		if (solid.isCollidable && AabbsOverlap(box, other)) {
			return true;
		}
	}

	return false;
}

bool Actor::MoveX(float amount)
{
	xRemainder += amount;
	int move = roundf(xRemainder);

	int sign = Sign(move);
	xRemainder -= move;
	while (move != 0) {
		if (!CollideAt(solids, position + IVector2{sign, 0})) {
			move -= sign;
			position.x += sign;
		} else {
			return true;
		}
	}

	return false;
}

bool Actor::MoveY(float amount)
{
	yRemainder += amount;
	int move = roundf(yRemainder);

	int sign = Sign(move);
	yRemainder -= move;
	while (move != 0) {
		if (!CollideAt(solids, position + IVector2{0, sign})) {
			move -= sign;
			position.y += sign;
		} else {
			return true;
		}
	}

	return false;
}

} // namespace Plat
