#ifndef PATROLENEMY_H
#define PATROLENEMY_H

#include "Enemy.h"

class PatrolEnemy : public Enemy {
private:
    Vector2 startPoint;
    Vector2 endPoint;
    bool movingToEnd;

public:
    PatrolEnemy(Vector2 pointA, Vector2 pointB, float moveSpeed);

    void Update(float dt, Vector2 playerPos, const GameConfig& config) override;
    void Reset() override;
    void Draw() const override;
};

#endif
