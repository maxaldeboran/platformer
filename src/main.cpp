#include <cmath>
#include <vector>

#include <raylib.h>

#include "util.h"

class Solid {
public:
	IVector2 position;
	Aabb hitbox;
	bool isCollidable = 1;

	constexpr int loX(void);
	constexpr int loY(void);
	constexpr int hiX(void);
	constexpr int hiY(void);

	constexpr Aabb GetHitboxTranslated(void);
	void Move(float x, float y);
private:
	float xRemainder, yRemainder;
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

class Actor {
public:
	IVector2 position;
	Aabb hitbox;
	bool isRidingCurrent = 0; /* used for Solid.Move() */

	constexpr int loX(void);
	constexpr int loY(void);
	constexpr int hiX(void);
	constexpr int hiY(void);

	bool MoveX(float amount); /* returns true if the movement hit a solid */
	bool MoveY(float amount); /* returns true if the movement hit a solid */
	bool CollideAt(const std::vector<Solid> &solids, IVector2 position);
	constexpr Aabb GetHitboxTranslated(void);
	virtual bool IsRiding(const Solid &solid);
	virtual void Squish(void);
private:
	float xRemainder, yRemainder;
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

class Game {
public:
	std::vector<Solid> solids;
	std::vector<Actor> actors;
	Actor *player;
} g_game;

void Solid::Move(float amountX, float amountY)
{
	xRemainder += amountX;
	yRemainder += amountY;
	int moveX = roundf(xRemainder);
	int moveY = roundf(yRemainder);

	if (moveX == 0 && moveY == 0) {
		return;
	}

	for (auto actor : g_game.actors) {
		actor.isRidingCurrent = actor.IsRiding(*this);
	}

	isCollidable = false;

	if (moveX != 0) {
		xRemainder -= moveX;
		position.x += moveX;

		if (moveX > 0) {
			for (auto &actor : g_game.actors) {
				if (AabbsOverlap(GetHitboxTranslated(), actor.GetHitboxTranslated())) {
					bool hit = actor.MoveX(hiX() - actor.loX() + 1);
					if (hit) actor.Squish();
				} else if (actor.isRidingCurrent) {
					bool hit = actor.MoveX(moveX);
					if (hit) actor.Squish();
				}
			}
		} else {
			for (auto &actor : g_game.actors) {
				if (AabbsOverlap(GetHitboxTranslated(), actor.GetHitboxTranslated())) {
					bool hit = actor.MoveX(loX() - actor.hiX() - 1);
					if (hit) actor.Squish();
				} else if (actor.isRidingCurrent) {
					bool hit = actor.MoveX(moveX);
					if (hit) actor.Squish();
				}
			}
		}
	}

	if (moveY != 0) {
		yRemainder -= moveY;
		position.y += moveY;

		if (moveY > 0) {
			for (auto &actor : g_game.actors) {
				if (AabbsOverlap(GetHitboxTranslated(), actor.GetHitboxTranslated())) {
					bool hit = actor.MoveY(hiY() - actor.loY() + 1);
					if (hit) actor.Squish();
				} else if (actor.isRidingCurrent) {
					actor.MoveY(moveY);
				}
			}
		} else {
			for (auto &actor : g_game.actors) {
				if (AabbsOverlap(GetHitboxTranslated(), actor.GetHitboxTranslated())) {
					bool hit = actor.MoveY(loY() - actor.hiY() - 1);
					if (hit) actor.Squish();
				} else if (actor.isRidingCurrent) {
					actor.MoveY(moveY);
				}
			}
		}
	}

	isCollidable = true;
}

bool Actor::IsRiding(const Solid &solid)
{
	(void)solid;
	return false;
}

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

	if (move == 0) {
		return false;
	}

	int sign = Sign(move);
	xRemainder -= move;
	while (move != 0) {
		if (!CollideAt(g_game.solids, position + IVector2{sign, 0})) {
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

	if (move == 0) {
		return false;
	}

	int sign = Sign(move);
	yRemainder -= move;
	while (move != 0) {
		if (!CollideAt(g_game.solids, position + IVector2{0, sign})) {
			move -= sign;
			position.y += sign;
		} else {
			return true;
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

	g_game.player = &g_game.actors.emplace_back();
	g_game.player->hitbox.hi = IVector2{31, 31};

	int solidIndex = 0;

	{
		Solid solid{};
		solid.position = IVector2{200, 200 - 47};
		solid.hitbox.hi = IVector2{47, 47};
		g_game.solids.push_back(solid);

		solidIndex = g_game.solids.size();

		solid = Solid{};
		solid.position = IVector2{50, 50};
		solid.hitbox.hi = IVector2{47, 47};
		g_game.solids.push_back(solid);

		solid = Solid{};
		solid.position = IVector2{200 - 47, 200};
		solid.hitbox.hi = IVector2{47, 47};
		g_game.solids.push_back(solid);
	}

	while (!WindowShouldClose()) {
		int dirX = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
		int dirY = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);
		g_game.player->MoveX(dirX * 100.0f * GetFrameTime()); 
		g_game.player->MoveY(dirY * 100.0f * GetFrameTime()); 

		g_game.solids[solidIndex].Move(20.0f * GetFrameTime(), 20.0f * GetFrameTime());

		BeginDrawing();
		ClearBackground(WHITE);
		DrawText("Hello World", 10, 10, 20, BLACK);

		for (auto actor : g_game.actors) {
			Rectangle rec = actor.GetHitboxTranslated().AsRec();
			DrawRectangleLinesEx(rec, 1.0f, RED);
		}
		for (auto solid : g_game.solids) {
			Rectangle rec = solid.GetHitboxTranslated().AsRec();
			DrawRectangleLinesEx(rec, 1.0f, BLUE);
		}
		EndDrawing();
	}

	return 0;
}
