#include "Enemy.h"

Enemy::Enemy(Vector2 startPos, float enemyRadius, float moveSpeed)
    : position(startPos), radius(enemyRadius), speed(moveSpeed) {}

void Enemy::ClampToPlayableArea(const GameConfig& config) {
    float minX = radius;
    float maxX = static_cast<float>(config.screenWidth) - radius;
    float minY = static_cast<float>(config.hudHeight) + radius;
    float maxY = static_cast<float>(config.screenHeight) - radius;

    if (position.x < minX) position.x = minX;
    if (position.x > maxX) position.x = maxX;
    if (position.y < minY) position.y = minY;
    if (position.y > maxY) position.y = maxY;
}

bool Enemy::CheckPlayerCollision(Vector2 playerPos, float playerRadius) const {
    return CheckCollisionCircles(position, radius, playerPos, playerRadius);
}
