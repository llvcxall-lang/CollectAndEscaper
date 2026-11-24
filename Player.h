#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "GameConfig.h"

class Player {
private:
    Vector2 position;
    float radius;
    int health;
    float damageCooldownTimer;

public:
    Player(const GameConfig& config);

    void Reset(const GameConfig& config);
    void Update(float dt, const GameConfig& config);
    void ClampToPlayableArea(const GameConfig& config);
    bool TryTakeDamage(const GameConfig& config);
    void Draw() const;

    Vector2 GetPosition() const { return position; }
    float GetRadius() const { return radius; }
    int GetHealth() const { return health; }
    float GetDamageCooldown() const { return damageCooldownTimer; }
};

#endif
