#ifndef CHASEENEMY_H
#define CHASEENEMY_H

#include "Enemy.h"

class ChaseEnemy : public Enemy {
private:
    Vector2 spawnPoint;

public:
    ChaseEnemy(Vector2 spawnPos, float moveSpeed);

    void Update(float dt, Vector2 playerPos, const GameConfig& config) override;
    void Reset() override;
    void Draw() const override;
};

#endif
