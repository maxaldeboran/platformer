#include "player.h"

#include <math.h>

#include <raylib.h>

#include "globals.h"

namespace Plat {

Player::Player(void) {
	TraceLog(LOG_INFO, "player constructor");
	hitbox.hi = IVector2{23, 23};

	isLanded = (velocity.y >= 0.0f && CollideAt(gGame->solids, position + IVector2{0, 1}));
}

void Player::Update(float dt) {
	if (IsKeyPressed(KEY_G)) {
		DeleteSelf();
	}

	constexpr float walkSpeed = 256.0f;

	int dirX = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);

	/* smooth acceleration */
	if (dirX != 0) {
		/* accelerate to walking speed in 4 frames */
		constexpr float accel = walkSpeed / (4.0f / 60);
		velocity.x += dirX * accel * dt;
	} else if (fabsf(velocity.x) > EPSILON) {
		/* deccelerat in 2 frames */
		constexpr float accel = walkSpeed / (2.0f / 60);
		int sign = Sign(velocity.x);
		velocity.x -= sign * accel * dt;
		if (sign * velocity.x <= sign * -EPSILON) {
			velocity.x = 0.0f;
		}
	}

	if (velocity.x > walkSpeed) {
		velocity.x = walkSpeed;
	} else if (velocity.x < -walkSpeed) {
		velocity.x = -walkSpeed;
	}


	int hitX = MoveX(velocity.x * dt); 
	if (hitX) {
		velocity.x = 0.0f;
	}

	float maxYVel = 288.0f;
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
	(void)hitY;

	isLanded = (velocity.y >= 0.0f && CollideAt(gGame->solids, position + IVector2{0, 1}));
}

bool Player::IsRiding(const Solid &solid)
{
	return solid.isCollidable && solid.loY() == hiY() + 1;
}

} // namespace Plat
