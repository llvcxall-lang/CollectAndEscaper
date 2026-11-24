#include "Game.h"
#include "PatrolEnemy.h"
#include "ChaseEnemy.h"

Game::Game()
    : config(),
      state(GameState::TITLE),
      player(config),
      enemies{ nullptr, nullptr },
      exitDoor{ 725.0f, 215.0f, 48.0f, 68.0f },
      exitUnlocked(false),
      score(0),
      timeRemaining(config.roundDuration),
      shouldQuit(false) {
    enemies[0] = new PatrolEnemy({ 340.0f, 100.0f }, { 340.0f, 405.0f }, config.patrolSpeed);
    enemies[1] = new ChaseEnemy({ 620.0f, 115.0f }, config.chaseSpeed);
    ResetRoundData();
}

Game::~Game() {
    for (int i = 0; i < TOTAL_ENEMIES; ++i) {
        delete enemies[i];
        enemies[i] = nullptr;
    }
}

void Game::ResetRoundData() {
    player.Reset(config);

    const std::array<Vector2, TOTAL_COINS> coinPositions = {{
        { 190.0f, 115.0f },
        { 220.0f, 385.0f },
        { 450.0f, 250.0f },
        { 580.0f, 120.0f },
        { 580.0f, 390.0f }
    }};

    for (int i = 0; i < TOTAL_COINS; ++i) {
        coins[i].Reset(coinPositions[i]);
    }

    for (int i = 0; i < TOTAL_ENEMIES; ++i) {
        if (enemies[i] != nullptr) {
            enemies[i]->Reset();
        }
    }

    exitUnlocked = false;
    score = 0;
    timeRemaining = config.roundDuration;
}

void Game::Update(float dt) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        shouldQuit = true;
        return;
    }

    if (IsKeyPressed(KEY_R)) {
        ResetRoundData();
        state = GameState::TITLE;
        return;
    }

    switch (state) {
        case GameState::TITLE:
            if (IsKeyPressed(KEY_ENTER)) {
                ResetRoundData();
                state = GameState::PLAYING;
            }
            break;

        case GameState::PLAYING:
            if (IsKeyPressed(KEY_P)) {
                state = GameState::PAUSED;
                return;
            }
            UpdateGameplay(dt);
            break;

        case GameState::PAUSED:
            if (IsKeyPressed(KEY_P)) {
                state = GameState::PLAYING;
            }
            break;

        case GameState::WIN:
        case GameState::LOSE:
            if (IsKeyPressed(KEY_ENTER)) {
                ResetRoundData();
                state = GameState::PLAYING;
            }
            break;
    }
}

void Game::UpdateGameplay(float dt) {
    timeRemaining -= dt;
    if (timeRemaining < 0.0f) {
        timeRemaining = 0.0f;
    }

    player.Update(dt, config);

    for (int i = 0; i < TOTAL_COINS; ++i) {
        score += coins[i].TryCollect(player.GetPosition(), player.GetRadius());
    }

    if (score >= TOTAL_COINS) {
        exitUnlocked = true;
    }

    for (int i = 0; i < TOTAL_ENEMIES; ++i) {
        if (enemies[i] != nullptr) {
            enemies[i]->Update(dt, player.GetPosition(), config);
            if (enemies[i]->CheckPlayerCollision(player.GetPosition(), player.GetRadius())) {
                player.TryTakeDamage(config);
            }
        }
    }

    bool hasLost = (player.GetHealth() <= 0) || (timeRemaining <= 0.0f);
    bool hasWon = exitUnlocked && CheckCollisionCircleRec(player.GetPosition(), player.GetRadius(), exitDoor);

    if (hasLost) {
        state = GameState::LOSE;
    } else if (hasWon) {
        state = GameState::WIN;
    }
}

void Game::DrawHUD() const {
    DrawRectangle(0, 0, config.screenWidth, config.hudHeight, DARKSLATEGRAY);
    DrawLine(0, config.hudHeight, config.screenWidth, config.hudHeight, LIGHTGRAY);

    int remainingCoins = TOTAL_COINS - score;
    DrawText(TextFormat("Health: %d", player.GetHealth()), 16, 10, 20, WHITE);
    DrawText(TextFormat("Score: %d / %d", score, TOTAL_COINS), 155, 10, 20, GOLD);
    DrawText(TextFormat("Remaining: %d", remainingCoins), 330, 10, 20, RAYWHITE);
    DrawText(TextFormat("Time: %.1fs", timeRemaining), 500, 10, 20, (timeRemaining <= 10.0f) ? RED : GREEN);
    DrawText("Arrows: Move | P: Pause | R: Reset | ESC: Quit", 16, 35, 14, LIGHTGRAY);
}

void Game::DrawGameplay() const {
    Color exitColor = exitUnlocked ? GREEN : GRAY;
    DrawRectangleRec(exitDoor, exitColor);
    DrawRectangleLinesEx(exitDoor, 2.0f, WHITE);
    DrawText(exitUnlocked ? "EXIT" : "LOCK", static_cast<int>(exitDoor.x + 8), static_cast<int>(exitDoor.y + 26), 14, BLACK);

    for (int i = 0; i < TOTAL_COINS; ++i) {
        coins[i].Draw();
    }

    for (int i = 0; i < TOTAL_ENEMIES; ++i) {
        if (enemies[i] != nullptr) {
            enemies[i]->Draw();
        }
    }

    player.Draw();
}

void Game::DrawOverlay(const char* title, const char* subtitle, Color titleColor) const {
    DrawRectangle(0, config.hudHeight, config.screenWidth, config.screenHeight - config.hudHeight, Fade(BLACK, 0.72f));
    int titleWidth = MeasureText(title, 36);
    int subWidth = MeasureText(subtitle, 20);
    DrawText(title, (config.screenWidth - titleWidth) / 2, 185, 36, titleColor);
    DrawText(subtitle, (config.screenWidth - subWidth) / 2, 240, 20, RAYWHITE);
}

void Game::Draw() const {
    ClearBackground(Color{ 24, 28, 36, 255 });
    DrawHUD();
    DrawGameplay();

    switch (state) {
        case GameState::TITLE:
            DrawOverlay("COLLECT AND ESCAPE", "Collect 5 coins, avoid enemies, reach exit. Press ENTER to Start", SKYBLUE);
            break;
        case GameState::PAUSED:
            DrawOverlay("PAUSED", "Simulation and timers frozen. Press P to Resume or R to Reset", YELLOW);
            break;
        case GameState::WIN:
            DrawOverlay("YOU ESCAPED!", "All 5 coins collected and exit reached. Press ENTER or R", GREEN);
            break;
        case GameState::LOSE:
            DrawOverlay("GAME OVER", "Health depleted or time expired. Press ENTER or R", RED);
            break;
        case GameState::PLAYING:
            break;
    }
}
