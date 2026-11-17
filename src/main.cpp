#include <cmath>
#include <vector>

#include <raylib.h>

#include "actor.h"
#include "globals.h"
#include "solid.h"
#include "util.h"

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
