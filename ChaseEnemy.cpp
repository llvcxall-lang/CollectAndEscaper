#include "ChaseEnemy.h"
#include <cmath>

ChaseEnemy::ChaseEnemy(Vector2 spawnPos, float moveSpeed)
    : Enemy(spawnPos, 15.0f, moveSpeed), spawnPoint(spawnPos) {}

void ChaseEnemy::Update(float dt, Vector2 playerPos, const GameConfig& config) {
    Vector2 delta = { playerPos.x - position.x, playerPos.y - position.y };
    float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (dist > 1.0f) {
        position.x += (delta.x / dist) * speed * dt;
        position.y += (delta.y / dist) * speed * dt;
    }

    ClampToPlayableArea(config);
}

void ChaseEnemy::Reset() {
    position = spawnPoint;
}

void ChaseEnemy::Draw() const {
    DrawCircleV(position, radius, PURPLE);
    DrawCircleLines(static_cast<int>(position.x), static_cast<int>(position.y), radius, DARKPURPLE);
}
