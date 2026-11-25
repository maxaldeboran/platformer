#include <cmath>
#include <vector>

#include <raylib.h>

#include "actor.h"
#include "globals.h"
#include "player.h"
#include "solid.h"
#include "util.h"

static const IVector2 gBlockPositions[] = {
	{ 0, 0 },
	{ 0, 32 },
	{ 0, 64 },
	{ 0, 96 },
	{ 0, 128 },
	{ 0, 160 },
	{ 0, 192 },
	{ 0, 224 },
	{ 0, 256 },

	{ 480, 0 },
	{ 480, 32 },
	{ 480, 64 },
	{ 480, 96 },
	{ 480, 128 },
	{ 480, 160 },
	{ 480, 192 },
	{ 480, 224 },
	{ 480, 256 },

	{ 32,  0 },
	{ 64,  0 },
	{ 96,  0 },
	{ 128, 0 },
	{ 160, 0 },
	{ 192, 0 },
	{ 224, 0 },
	{ 256, 0 },
	{ 288, 0 },
	{ 320, 0 },
	{ 352, 0 },
	{ 384, 0 },
	{ 416, 0 },
	{ 448, 0 },

	{ 32,  256 },
	{ 64,  256 },
	{ 96,  256 },
	{ 128, 256 },
	{ 160, 256 },
	{ 192, 256 },
	{ 224, 256 },
	{ 256, 256 },
	{ 288, 256 },
	{ 320, 256 },
	{ 352, 256 },
	{ 384, 256 },
	{ 416, 256 },
	{ 448, 256 },
};

int main(void)
{
	SetTraceLogLevel(LOG_DEBUG);

	InitWindow(512, 288, "Hello World");
	if (!IsWindowReady()) {
		TraceLog(LOG_FATAL, "Failed to initialize the window");
	}

	SetTargetFPS(60);

	Plat::gGame = new Plat::Game;

	Plat::Player player{};
	player.position = {100, 100};
	Plat::gGame->level.actors.push_back(std::make_shared<Plat::Player>(player));

	for (size_t i = 0; i < sizeof(gBlockPositions) / sizeof(*gBlockPositions); i++) {
		Plat::Solid solid{};
		solid.position = gBlockPositions[i];
		solid.hitbox.hi = {31, 31};
		Plat::gGame->solids.push_back(std::make_shared<Plat::Solid>(solid));
	}

	while (!WindowShouldClose()) {
		Plat::gGame->level.Update(GetFrameTime());

		BeginDrawing();
		ClearBackground(WHITE);

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
