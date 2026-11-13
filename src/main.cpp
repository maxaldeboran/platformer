#include <math.h>

#include <raylib.h>

constexpr int Sign(int x) {
	return (x > 0) - (x < 0);
}

constexpr int Sign(float x) {
	float eps = 0.0f;
	return (x >= eps) - (x <= -eps);
}

struct IVector2 {
	int x, y;
};

class Solid {
public:
	IVector2 GetPosition(void) {
		return position;
	}

	int GetX(void) {
		return position.x;
	}

	int GetY(void) {
		return position.y;
	}

private:
	IVector2 position;
	float xRemainder, yRemainder;
};

class Actor {
public:
	IVector2 GetPosition(void) {
		return position;
	}

	int GetX(void) {
		return position.x;
	}

	int GetY(void) {
		return position.y;
	}

	bool MoveX(float amount) {
		xRemainder += amount;
		int move = roundf(xRemainder);

		if (move != 0) {
			xRemainder -= move;
			/* TODO: proper movement/collision code */
			position.x += move;
		}

		return false;
	}

	bool MoveY(float amount) {
		yRemainder += amount;
		int move = roundf(yRemainder);

		if (move != 0) {
			yRemainder -= move;
			/* TODO: proper movement/collision code */
			position.y += move;
		}

		return false;
	}

private:
	IVector2 position;
	float xRemainder, yRemainder;
};

class Game {
public:
	Actor player;
};

Game gGame;

int main(void) {
	InitWindow(512, 288, "Hello World");
	if (!IsWindowReady()) {
		TraceLog(LOG_FATAL, "Failed to initialize the window");
	}

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		int dirX = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
		int dirY = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);
		gGame.player.MoveX(dirX * 100.0f * GetFrameTime()); 
		gGame.player.MoveY(dirY * 100.0f * GetFrameTime()); 

		BeginDrawing();
		ClearBackground(WHITE);
		DrawText("Hello World", 10, 10, 20, BLACK);

		Rectangle rec = {
			.x = (float)gGame.player.GetX(),
			.y = (float)gGame.player.GetY(),
			.width = 32.0f,
			.height = 32.0f,
		};
		DrawRectangleRec(rec, RED);
		EndDrawing();
	}

	return 0;
}
