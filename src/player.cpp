#include "player.h"

#include <math.h>

#include <raylib.h>

#include "globals.h"

namespace Plat {

Player::Player(void) {
	TraceLog(LOG_INFO, "player constructor");
	hitbox = Aabb{.lo = {-12, -23}, .hi = {11, 0}};

	isLanded = (velocity.y >= 0.0f && CollideAt(gGame->level.solids, position + IVector2{0, 1}));

	walkTexture = gGame->resman.GetTexture("player");
	idleTexture = gGame->resman.GetTexture("playerIDLE");
}

void Player::Draw(void) {
	Rectangle dest{};
	Rectangle source{};
	Texture texture{};

	int frames = 1;
	float frameTime = 1.0f;

	dest.y = 8;
	dest.width = 64;
	dest.height = 64;
	if (!isWalking) {
		dest.x = 0;
		texture = idleTexture;
		frames = 27;
		frameTime = 0.2f;
	} else {
		dest.x = 3;
		texture = walkTexture;
		frames = 16;
		frameTime = 0.06f;
	}

	int frame = (int)(animationTime / frameTime) % frames;
	source.x = 128 * (frame % 4);
	source.y = 128 * (frame / 4);
	source.width = 128;
	source.height = 128;

	if (isSpriteFlipX) {
		dest.x *= -1;
		source.width *= -1;
	}

	dest.x = position.x - 32 + dest.x;
	dest.y = position.y - 64 + dest.y;

	DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);
}

void Player::Update(float dt) {
	if (IsKeyPressed(KEY_G)) {
		DeleteSelf();
	}

	constexpr float walkSpeed = 256.0f;

	int dirX = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);

	/* smooth acceleration */
	if (dirX != 0) {
		/* accelerate to walking speed in 10 frames */
		constexpr float accel = walkSpeed / (10.0f / 60);
		velocity.x += dirX * accel * dt;
	} else if (fabsf(velocity.x) > EPSILON) {
		/* deccelerate in 2 frames */
		constexpr float accel = walkSpeed / (10.0f / 60);
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

	isLanded = (velocity.y >= 0.0f && CollideAt(gGame->level.solids, position + IVector2{0, 1}));

	/* anim */

	bool wasWalking = isWalking;

	if (velocity.x > EPSILON) {
		isSpriteFlipX = false;
		isWalking = true;
	} else if (velocity.x < -EPSILON) {
		isSpriteFlipX = true;
		isWalking = true;
	} else if (isLanded) {
		isWalking = false;
	}

	if (isWalking != wasWalking) {
		animationTime = 0.0f;
	} else {
		animationTime += dt;
	}
}

bool Player::IsRiding(const Solid &solid)
{
	return solid.isCollidable && solid.loY() == hiY() + 1;
}

} // namespace Plat
