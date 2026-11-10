#include <raylib.h>

int main(void)
{
	InitWindow(800, 600, "Hello World");
	if (!IsWindowReady()) {
		TraceLog(LOG_FATAL, "Failed to initialize the window");
	}

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);
		DrawText("Hello World", 10, 10, 20, BLACK);
		EndDrawing();
	}

	return 0;
}
