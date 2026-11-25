#include "player.h"

#include <raylib.h>

#include "globals.h"

namespace Plat {

Player::Player(void) {
	TraceLog(LOG_INFO, "player constructor");
	hitbox.hi = IVector2{23, 23};

	isLanded = (velocity.y >= 0.0f && CollideAt(gGame->solids, position + IVector2{0, 1}));
}

void Player::Update(float dt) {
	int dirX = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
	MoveX(dirX * 256.0f * dt); 

	int maxYVel = 288.0f;
	velocity.y += gGame->level.gravity.y * dt;
	if (velocity.y > maxYVel) {
		velocity.y = maxYVel;
	}

	if (isLanded) {
		if (velocity.y > 0.0f) {
			velocity.y = 0.0f;
		}
		if (IsKeyPressed(KEY_SPACE)) {
			velocity.y = -288.0f * 1.75f;
			isJumpControlled = true;
			isLanded = false;
		}
	}

	isJumpControlled = isJumpControlled && velocity.y < 0.0f;

	if (isJumpControlled && IsKeyReleased(KEY_SPACE)) {
		isJumpControlled = false;
		velocity.y = 0.0f;
	}

	bool hitY = MoveY(velocity.y * dt); 

	isLanded = (velocity.y >= 0.0f && CollideAt(gGame->solids, position + IVector2{0, 1}));

	TraceLog(LOG_DEBUG, TextFormat("Landed: %i", (int)isLanded));
	TraceLog(LOG_DEBUG, TextFormat("Y velocity: %f", velocity.y));
	TraceLog(LOG_DEBUG, TextFormat("Y hit: %i", (int)hitY));
	TraceLog(LOG_DEBUG, TextFormat("Controlled jump: %i", (int)isJumpControlled));
}

bool Player::IsRiding(const Solid &solid)
{
	return solid.isCollidable && solid.loY() == hiY() + 1;
}

} // namespace Plat
