#include "Player.h"

Player::Player(const GameConfig& config)
    : position{ 80.0f, 240.0f }, radius(16.0f), health(config.startingHealth), damageCooldownTimer(0.0f) {
    Reset(config);
}

void Player::Reset(const GameConfig& config) {
    position = { 80.0f, static_cast<float>(config.hudHeight + (config.screenHeight - config.hudHeight) / 2) };
    health = config.startingHealth;
    damageCooldownTimer = 0.0f;
    ClampToPlayableArea(config);
}

void Player::Update(float dt, const GameConfig& config) {
    if (damageCooldownTimer > 0.0f) {
        damageCooldownTimer -= dt;
        if (damageCooldownTimer < 0.0f) {
            damageCooldownTimer = 0.0f;
        }
    }

    Vector2 dir = { 0.0f, 0.0f };
    if (IsKeyDown(KEY_RIGHT)) dir.x += 1.0f;
    if (IsKeyDown(KEY_LEFT))  dir.x -= 1.0f;
    if (IsKeyDown(KEY_DOWN))  dir.y += 1.0f;
    if (IsKeyDown(KEY_UP))    dir.y -= 1.0f;

    position.x += dir.x * config.playerSpeed * dt;
    position.y += dir.y * config.playerSpeed * dt;

    ClampToPlayableArea(config);
}

void Player::ClampToPlayableArea(const GameConfig& config) {
    float minX = radius;
    float maxX = static_cast<float>(config.screenWidth) - radius;
    float minY = static_cast<float>(config.hudHeight) + radius;
    float maxY = static_cast<float>(config.screenHeight) - radius;

    if (position.x < minX) position.x = minX;
    if (position.x > maxX) position.x = maxX;
    if (position.y < minY) position.y = minY;
    if (position.y > maxY) position.y = maxY;
}

bool Player::TryTakeDamage(const GameConfig& config) {
    if (damageCooldownTimer > 0.0f || health <= 0) {
        return false;
    }
    health -= 1;
    if (health < 0) {
        health = 0;
    }
    damageCooldownTimer = config.damageCooldown;
    return true;
}

void Player::Draw() const {
    Color playerColor = (damageCooldownTimer > 0.0f) ? ORANGE : SKYBLUE;
    DrawCircleV(position, radius, playerColor);
    DrawCircleLines(static_cast<int>(position.x), static_cast<int>(position.y), radius, DARKBLUE);
}
