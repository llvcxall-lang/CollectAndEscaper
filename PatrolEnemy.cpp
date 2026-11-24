#include "PatrolEnemy.h"
#include <cmath>

PatrolEnemy::PatrolEnemy(Vector2 pointA, Vector2 pointB, float moveSpeed)
    : Enemy(pointA, 15.0f, moveSpeed), startPoint(pointA), endPoint(pointB), movingToEnd(true) {}

void PatrolEnemy::Update(float dt, Vector2 playerPos, const GameConfig& config) {
    (void)playerPos;
    Vector2 target = movingToEnd ? endPoint : startPoint;
    Vector2 delta = { target.x - position.x, target.y - position.y };
    float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (dist <= speed * dt || dist < 1.0f) {
        position = target;
        movingToEnd = !movingToEnd;
    } else {
        position.x += (delta.x / dist) * speed * dt;
        position.y += (delta.y / dist) * speed * dt;
    }

    ClampToPlayableArea(config);
}

void PatrolEnemy::Reset() {
    position = startPoint;
    movingToEnd = true;
}

void PatrolEnemy::Draw() const {
    DrawRectangle(
        static_cast<int>(position.x - radius),
        static_cast<int>(position.y - radius),
        static_cast<int>(radius * 2.0f),
        static_cast<int>(radius * 2.0f),
        RED
    );
    DrawRectangleLines(
        static_cast<int>(position.x - radius),
        static_cast<int>(position.y - radius),
        static_cast<int>(radius * 2.0f),
        static_cast<int>(radius * 2.0f),
        MAROON
    );
}
