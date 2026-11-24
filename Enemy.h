#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "GameConfig.h"

class Enemy {
protected:
    Vector2 position;
    float radius;
    float speed;

    void ClampToPlayableArea(const GameConfig& config);

public:
    Enemy(Vector2 startPos, float enemyRadius, float moveSpeed);
    virtual ~Enemy() = default;

    virtual void Update(float dt, Vector2 playerPos, const GameConfig& config) = 0;
    virtual void Reset() = 0;
    virtual void Draw() const = 0;

    bool CheckPlayerCollision(Vector2 playerPos, float playerRadius) const;
    Vector2 GetPosition() const { return position; }
};

#endif
