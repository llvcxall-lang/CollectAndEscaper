#ifndef GAME_H
#define GAME_H

#include <array>
#include "raylib.h"
#include "GameConfig.h"
#include "Player.h"
#include "Coin.h"
#include "Enemy.h"

enum class GameState {
    TITLE,
    PLAYING,
    PAUSED,
    WIN,
    LOSE
};

class Game {
private:
    static constexpr int TOTAL_COINS = 5;
    static constexpr int TOTAL_ENEMIES = 2;

    GameConfig config;
    GameState state;
    Player player;
    std::array<Coin, TOTAL_COINS> coins;
    std::array<Enemy*, TOTAL_ENEMIES> enemies;

    Rectangle exitDoor;
    bool exitUnlocked;
    int score;
    float timeRemaining;
    bool shouldQuit;

    void ResetRoundData();
    void UpdateGameplay(float dt);
    void DrawHUD() const;
    void DrawGameplay() const;
    void DrawOverlay(const char* title, const char* subtitle, Color titleColor) const;

public:
    Game();
    ~Game();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void Update(float dt);
    void Draw() const;
    bool ShouldQuit() const { return shouldQuit; }
};

#endif
