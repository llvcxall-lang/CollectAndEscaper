#ifndef GAMECONFIG_H
#define GAMECONFIG_H

struct GameConfig {
    int screenWidth = 800;
    int screenHeight = 450;
    int hudHeight = 56;

    int startingHealth = 3;
    float roundDuration = 60.0f;
    float playerSpeed = 220.0f;
    float damageCooldown = 1.0f;

    float patrolSpeed = 140.0f;
    float chaseSpeed = 115.0f;
};

#endif
