#ifndef COIN_H
#define COIN_H

#include "raylib.h"

class Coin {
private:
    Vector2 position;
    float radius;
    int value;
    bool active;

public:
    Coin();
    Coin(Vector2 pos, int coinValue = 1, float coinRadius = 10.0f);

    void Reset(Vector2 pos);
    int TryCollect(Vector2 playerPos, float playerRadius);
    void Draw() const;

    bool IsActive() const { return active; }
    Vector2 GetPosition() const { return position; }
};

#endif
