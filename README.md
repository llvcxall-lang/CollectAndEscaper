# Collect and Escape (C++ & Raylib)

A 2D object-oriented survival and collection game built with C++17 and Raylib.

## Build & Run Steps
### Using g++ (MinGW / Windows)
```bash
g++ -std=c++17 main.cpp Game.cpp Player.cpp Coin.cpp Enemy.cpp PatrolEnemy.cpp ChaseEnemy.cpp -o CollectAndEscape.exe -lraylib -lopengl32 -lgdi32 -lwinmm
./CollectAndEscape.exe
```
### Using Linux / macOS
```bash
g++ -std=c++17 main.cpp Game.cpp Player.cpp Coin.cpp Enemy.cpp PatrolEnemy.cpp ChaseEnemy.cpp -o CollectAndEscape -lraylib -lm -lpthread -ldl -lrt -lX11
./CollectAndEscape
```

## Controls
- **Arrow Keys (Up/Down/Left/Right):** Move player inside playable area
- **ENTER:** Start game from Title screen (or restart after Win/Lose)
- **P:** Pause / Resume gameplay (freezes all timers and simulation)
- **R:** Reset all game data from `GameConfig` and return to Title screen
- **ESC:** Exit the application

## Normal `GameConfig` Values (`GameConfig.h`)
- `screenWidth = 800`, `screenHeight = 450`, `hudHeight = 56`
- `startingHealth = 3`
- `roundDuration = 60.0f` seconds
- `playerSpeed = 220.0f` px/s
- `damageCooldown = 1.0f` second
- `patrolSpeed = 140.0f` px/s, `chaseSpeed = 115.0f` px/s

## Key Locations (File & Function Mapping)
- **Collision Detection:**
  - Coin collection: `Coin.cpp` -> `Coin::TryCollect()`
  - Enemy contact: `Enemy.cpp` -> `Enemy::CheckPlayerCollision()` called inside `Game.cpp` -> `Game::UpdateGameplay()`
  - Exit door check: `Game.cpp` -> `Game::UpdateGameplay()` (`CheckCollisionCircleRec`)
- **Reset Logic:** `Game.cpp` -> `Game::ResetRoundData()`, `Player.cpp` -> `Player::Reset()`, `Coin.cpp` -> `Coin::Reset()`, `PatrolEnemy.cpp` -> `PatrolEnemy::Reset()`, `ChaseEnemy.cpp` -> `ChaseEnemy::Reset()`
- **Enemy Ownership & Cleanup:** `Game.h` (`std::array<Enemy*, 2> enemies`), allocated once with `new` in `Game::Game()` (`Game.cpp`), deleted once via base `Enemy*` pointers with `delete` in `Game::~Game()` (`Game.cpp`).
- **Four OOP Principles:**
  1. **Encapsulation:** Private state (`position`, `health`, `damageCooldownTimer` in `Player.h`; `position`, `value`, `active` in `Coin.h`) modified only via controlled member functions (`Player::TryTakeDamage()`, `Coin::TryCollect()`).
  2. **Inheritance:** `PatrolEnemy` (`PatrolEnemy.h`) and `ChaseEnemy` (`ChaseEnemy.h`) publicly inherit from `Enemy`.
  3. **Polymorphism:** `Game::UpdateGameplay()` and `Game::DrawGameplay()` invoke `enemies[i]->Update(...)` and `enemies[i]->Draw()` through `Enemy*` base pointers.
  4. **Abstraction:** `Enemy` (`Enemy.h`) declares pure virtual methods (`Update`, `Reset`, `Draw`) and a `virtual ~Enemy() = default;` destructor, preventing direct instantiation.

## Known Issues & Credits
- **Known Issues:** None; all coins and exit door are tested to be reachable without overlap.
- **Credits:** Built using C++17 and Raylib primitive shapes.
