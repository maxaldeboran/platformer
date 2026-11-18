#include <cmath>
#include <vector>

#include <raylib.h>

#include "actor.h"
#include "globals.h"
#include "player.h"
#include "solid.h"
#include "util.h"

int main(void)
{
	InitWindow(512, 288, "Hello World");
	if (!IsWindowReady()) {
		TraceLog(LOG_FATAL, "Failed to initialize the window");
	}

	SetTargetFPS(60);

	Plat::gGame = new Plat::Game;

	Plat::gGame->level.actors.push_back(std::make_shared<Plat::Player>());

	int solidIndex = 0;

	{
		Plat::Solid solid;
		solid.position = IVector2{200, 200 - 47};
		solid.hitbox.hi = IVector2{47, 47};
		Plat::gGame->solids.push_back(std::make_shared<Plat::Solid>(solid));

		solidIndex = Plat::gGame->solids.size();

		solid = Plat::Solid();
		solid.position = IVector2{50, 50};
		solid.hitbox.hi = IVector2{47, 47};
		Plat::gGame->solids.push_back(std::make_shared<Plat::Solid>(solid));

		solid = Plat::Solid();
		solid.position = IVector2{200 - 47, 200};
		solid.hitbox.hi = IVector2{47, 47};
		Plat::gGame->solids.push_back(std::make_shared<Plat::Solid>(solid));
	}

	while (!WindowShouldClose()) {
		Plat::gGame->level.Update();

		Plat::gGame->solids[solidIndex]->Move(20.0f * GetFrameTime(), 20.0f * GetFrameTime());

		BeginDrawing();
		ClearBackground(WHITE);
		DrawText("Hello World", 10, 10, 20, BLACK);

		for (auto &actor : Plat::gGame->level.actors) {
			Rectangle rec = actor->GetHitboxTranslated().AsRec();
			DrawRectangleLinesEx(rec, 1.0f, RED);
		}
		for (auto &solid : Plat::gGame->solids) {
			Rectangle rec = solid->GetHitboxTranslated().AsRec();
			DrawRectangleLinesEx(rec, 1.0f, BLUE);
		}
		EndDrawing();
	}

	delete Plat::gGame;

	return 0;
}
