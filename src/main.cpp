#include <cmath>
#include <vector>

#include <raylib.h>

#include "util.h"

class Solid {
public:
	IVector2 position;
	Aabb hitbox;
	constexpr Aabb GetHitboxTranslated(void);
private:
	float xRemainder, yRemainder;
};

constexpr Aabb Solid::GetHitboxTranslated(void)
{
	return hitbox.Translated(position);
}

class Actor {
public:
	IVector2 position;
	Aabb hitbox;
	bool MoveX(float amount);
	bool MoveY(float amount);
	constexpr Aabb GetHitboxTranslated(void);
private:
	float xRemainder, yRemainder;
	bool CollideAt(const std::vector<Solid> &solids, IVector2 position);
};

constexpr Aabb Actor::GetHitboxTranslated(void)
{
	return hitbox.Translated(position);
}

class Game {
public:
	std::vector<Solid> solids;
	Actor player;
};

Game gGame;

bool Actor::CollideAt(const std::vector<Solid> &solids, IVector2 position)
{
	Aabb box = hitbox.Translated(position);

	for (auto solid : solids) {
		Aabb other = solid.hitbox.Translated(solid.position);

		if (AabbsCollide(box, other)) {
			return true;
		}
	}

	return false;
}

bool Actor::MoveX(float amount)
{
	xRemainder += amount;
	int move = roundf(xRemainder);

	if (move != 0) {
		int sign = Sign(move);
		xRemainder -= move;
		while (move != 0) {
			if (!CollideAt(gGame.solids, position + IVector2{sign, 0})) {
				move -= sign;
				position.x += sign;
			} else {
				return true;
			}
		}
	}

	return false;
}

bool Actor::MoveY(float amount)
{
	yRemainder += amount;
	int move = roundf(yRemainder);

	if (move != 0) {
		int sign = Sign(move);
		yRemainder -= move;
		while (move != 0) {
			if (!CollideAt(gGame.solids, position + IVector2{0, sign})) {
				move -= sign;
				position.y += sign;
			} else {
				return true;
			}
		}
	}

	return false;
}

int main(void)
{
	InitWindow(512, 288, "Hello World");
	if (!IsWindowReady()) {
		TraceLog(LOG_FATAL, "Failed to initialize the window");
	}

	SetTargetFPS(60);

	gGame.player.hitbox.hi = IVector2{23, 23};

	Solid solid{};
	solid.position = IVector2{100, 100};
	solid.hitbox.hi = IVector2{15, 15};
	gGame.solids.push_back(solid);

	while (!WindowShouldClose()) {
		int dirX = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
		int dirY = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);
		gGame.player.MoveX(dirX * 100.0f * GetFrameTime()); 
		gGame.player.MoveY(dirY * 100.0f * GetFrameTime()); 

		BeginDrawing();
		ClearBackground(WHITE);
		DrawText("Hello World", 10, 10, 20, BLACK);

		Rectangle rec = gGame.player.GetHitboxTranslated().AsRec();
		DrawRectangleLinesEx(rec, 1.0f, RED);
		for (auto solid : gGame.solids) {
			rec = solid.GetHitboxTranslated().AsRec();
			DrawRectangleLinesEx(rec, 1.0f, BLUE);
		}
		EndDrawing();
	}

	return 0;
}
