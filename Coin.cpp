#include "Coin.h"

Coin::Coin() : position{ 0.0f, 0.0f }, radius(10.0f), value(1), active(true) {}

Coin::Coin(Vector2 pos, int coinValue, float coinRadius)
    : position(pos), radius(coinRadius), value(coinValue), active(true) {}

void Coin::Reset(Vector2 pos) {
    position = pos;
    active = true;
}

int Coin::TryCollect(Vector2 playerPos, float playerRadius) {
    if (!active) {
        return 0;
    }
    if (CheckCollisionCircles(position, radius, playerPos, playerRadius)) {
        active = false;
        return value;
    }
    return 0;
}

void Coin::Draw() const {
    if (!active) {
        return;
    }
    DrawCircleV(position, radius, GOLD);
    DrawCircleLines(static_cast<int>(position.x), static_cast<int>(position.y), radius, ORANGE);
}
