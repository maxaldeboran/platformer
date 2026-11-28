#ifndef PLAT_PLAYER_H_
#define PLAT_PLAYER_H_

#include "actor.h"

namespace Plat {

class Player : public virtual Actor {
public:
	Vector2 velocity{0, 0};
	bool isLanded = false;
	bool isJumpControlled = false;

	Player(void);
	void Update(float dt) override;
	void Draw(void) override;
	bool IsRiding(const Solid &solid) override;
private:
	Texture walkTexture{};
	Texture idleTexture{};
	float animationTime = 0.0f;
	bool isSpriteFlipX = false;
	bool isWalking = false;
};

} // namespace Plat

#endif // PLAT_PLAYER_H_
