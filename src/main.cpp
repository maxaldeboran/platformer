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

	Plat::player = &Plat::actors.emplace_back();
	Plat::player->hitbox.hi = IVector2{31, 31};

	int solidIndex = 0;

	{
		Plat::Solid solid{};
		solid.position = IVector2{200, 200 - 47};
		solid.hitbox.hi = IVector2{47, 47};
		Plat::solids.push_back(solid);

		solidIndex = Plat::solids.size();

		solid = Plat::Solid{};
		solid.position = IVector2{50, 50};
		solid.hitbox.hi = IVector2{47, 47};
		Plat::solids.push_back(solid);

		solid = Plat::Solid{};
		solid.position = IVector2{200 - 47, 200};
		solid.hitbox.hi = IVector2{47, 47};
		Plat::solids.push_back(solid);
	}

	while (!WindowShouldClose()) {
		int dirX = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
		int dirY = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);
		Plat::player->MoveX(dirX * 100.0f * GetFrameTime()); 
		Plat::player->MoveY(dirY * 100.0f * GetFrameTime()); 

		Plat::solids[solidIndex].Move(20.0f * GetFrameTime(), 20.0f * GetFrameTime());

		BeginDrawing();
		ClearBackground(WHITE);
		DrawText("Hello World", 10, 10, 20, BLACK);

		for (auto actor : Plat::actors) {
			Rectangle rec = actor.GetHitboxTranslated().AsRec();
			DrawRectangleLinesEx(rec, 1.0f, RED);
		}
		for (auto solid : Plat::solids) {
			Rectangle rec = solid.GetHitboxTranslated().AsRec();
			DrawRectangleLinesEx(rec, 1.0f, BLUE);
		}
		EndDrawing();
	}

	return 0;
}
