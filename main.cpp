#include "raylib.h"
#include "GameConfig.h"
#include "Game.h"

int main() {
    GameConfig initialConfig;
    InitWindow(initialConfig.screenWidth, initialConfig.screenHeight, "Collect and Escape");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    {
        Game game;
        while (!WindowShouldClose() && !game.ShouldQuit()) {
            float dt = GetFrameTime();
            game.Update(dt);

            BeginDrawing();
            game.Draw();
            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}
