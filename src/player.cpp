#include "player.h"

#include <raylib.h>

namespace Plat {

Player::Player(void) {
	TraceLog(LOG_INFO,"player constructor");
	hitbox.hi = IVector2{31, 31};
}

void Player::Update(void) {
	int dirX = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
	int dirY = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);
	MoveX(dirX * 100.0f * GetFrameTime()); 
	MoveY(dirY * 100.0f * GetFrameTime()); 
}

} // namespace Plat
