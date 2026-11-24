# Collect and Escape — Class Diagram, Test Record & AI Use Log

---

## 1. One-Page Class Relationship & Ownership Diagram

```text
+-------------------------------------------------------------------+
|                           GameConfig                              |
|  (screenWidth, screenHeight, hudHeight, startingHealth=3,         |
|   roundDuration=60.0f, playerSpeed=220.0f, damageCooldown=1.0f)   |
+-------------------------------------------------------------------+
                                  ^
                                  | reads configuration
+-------------------------------------------------------------------+
|                               Game                                |
|  - config : GameConfig                                            |
|  - state : GameState (TITLE, PLAYING, PAUSED, WIN, LOSE)          |
|  - player : Player                   [Composition - Value Owner]  |
|  - coins : std::array<Coin, 5>       [Composition - Value Owner]  |
|  - enemies : std::array<Enemy*, 2>   [Sole Dynamic Heap Owner]    |
|  - exitDoor : Rectangle, exitUnlocked : bool                      |
|  - score : int, timeRemaining : float                             |
|  + Game()  -> allocates 1 PatrolEnemy & 1 ChaseEnemy via new      |
|  + ~Game() -> deletes both via Enemy* using delete (not delete[]) |
+-------------------------------------------------------------------+
         | owns (1)                | owns (5)               | owns (2 via Enemy*)
         v                         v                        v
+-------------------+   +---------------------+   +-------------------------------+
|      Player       |   |        Coin         |   |     <<abstract>> Enemy        |
| - position        |   | - position          |   | # position, radius, speed     |
| - radius          |   | - radius            |   | + virtual ~Enemy() = default  |
| - health          |   | - value             |   | + Update(...) = 0             |
| - damageCooldown  |   | - active            |   | + Reset() = 0, Draw() = 0     |
| + Update()        |   | + TryCollect()      |   | + CheckPlayerCollision()      |
| + TryTakeDamage() |   | + Draw()            |   +-------------------------------+
| + Reset()         |   | + Reset()           |             ^             ^
+-------------------+   +---------------------+             |             |
                                                   (public) |             | (public)
                                             +--------------------+ +--------------------+
                                             |    PatrolEnemy     | |     ChaseEnemy     |
                                             | - startPoint       | | - spawnPoint       |
                                             | - endPoint         | | + Update() override|
                                             | - movingToEnd      | | + Reset() override |
                                             | + Update() override| | + Draw() override  |
                                             +--------------------+ +--------------------+
```

---

## 2. Test & Development Record

### Feature Verification Table (F1 – F6)
| ID | Feature | Test Case | Expected Result | Actual Result | Status |
|---|---|---|---|---|---|
| **F1** | Player movement | Hold Arrow keys in all 4 directions and push against all 4 walls/HUD border. | Player moves smoothly using `dt` (`GetFrameTime()`) and full circle stays inside playable area (`y >= 56 + r`). | Player moves smoothly and stops cleanly at HUD and screen edges. | **PASS** |
| **F2** | Five coins & score | Collect each of the 5 coins and walk back over collected coin spots. | Each coin awards +1 once, disappears (`active = false`), score increases to 5, remaining drops to 0. | Score increments 1..5 once per coin; revisiting empty spots gives 0 points. | **PASS** |
| **F3** | Two enemy behaviours | Observe `PatrolEnemy` and `ChaseEnemy` during `PLAYING` state. | `PatrolEnemy` moves between `(340,100)` and `(340,405)`; `ChaseEnemy` steers toward player; both stay inside playable area. | Both enemies follow expected paths and stay within bounds. | **PASS** |
| **F4** | Health & cooldown | Collide with enemy and stay overlapping for 0.5s, then 1.2s. | Health drops from 3 to 2 on first hit; no second hit during 1.0s cooldown; drops to 1 after cooldown expires. | Health drops once per 1.0s window; player turns orange during cooldown. | **PASS** |
| **F5** | Win & lose rules | (a) Touch exit with `<5` coins; (b) Collect 5 coins and touch exit; (c) Health reaches 0 simultaneously with exit/timer 0. | (a) Exit stays locked; (b) Exit unlocks (green) and triggers `WIN`; (c) `LOSE` takes priority over `WIN`. | Exit remains locked until 5 coins; `LOSE` triggers when health/time hits 0 even on exit. | **PASS** |
| **F6** | Complete game flow | Press `ENTER` on title, `P` during play, `R` mid-round, `ESC` anytime. | `ENTER` starts; `P` freezes timer/cooldown/enemies; `R` resets values from `GameConfig` to `TITLE`; `ESC` exits cleanly. | All state transitions and timer freezes behave as specified. | **PASS** |

### Development Snapshots (GitHub Commit Evidence)
- **Stage 1 (Working Objects):** Implemented `GameConfig`, `Player` movement/clamping, and 5 `Coin` objects with single-collection scoring. Verified with screenshot and Git commit `Stage 1: Working player movement and 5 coins`.
- **Stage 2 (OOP & Enemies):** Added abstract `Enemy` base class, `PatrolEnemy`, `ChaseEnemy`, polymorphic `Enemy*` array in `Game`, and 1.0s damage cooldown. Verified with screenshot and Git commit `Stage 2: Enemy polymorphism and health cooldown`.
- **Stage 3 (Complete Game):** Added `GameState` machine (`TITLE`, `PLAYING`, `PAUSED`, `WIN`, `LOSE`), exit door unlock rule, full reset, and clean destructor verification.

### Documented Bug & Retest
- **Bug Found:** Pressing `ESC` closed the window immediately via Raylib's default exit key instead of letting `Game::Update()` set `shouldQuit = true` and exit the main loop cleanly so `Game::~Game()` runs before `CloseWindow()`.
- **Fix Applied:** Added `SetExitKey(KEY_NULL);` in `main.cpp` and handled `IsKeyPressed(KEY_ESCAPE)` inside `Game::Update()`.
- **Retest Result:** Pressing `ESC` sets `shouldQuit = true`, exits the `while` loop cleanly, invokes `Game::~Game()` to delete both `Enemy*` pointers, and closes the window with zero leaks.

---

## 3. AI-Use Record (3 Entries)
1. **Assistance Requested:** Asked for class header organization separating `Enemy` pure virtual interface from `PatrolEnemy` and `ChaseEnemy`.
   - **Code/Decision Affected:** `Enemy.h`, `PatrolEnemy.h`, `ChaseEnemy.h` (`virtual ~Enemy() = default;` and `Update(...) = 0`).
   - **Verification/Change:** Compiled with `-Wall -Wextra` and verified direct instantiation of `Enemy` causes a compiler error as required.
2. **Assistance Requested:** Asked how to enforce loss priority over win if health or timer reaches zero in the exact same frame the player touches the unlocked exit.
   - **Code/Decision Affected:** `Game.cpp` inside `Game::UpdateGameplay()` (`if (hasLost) state = GameState::LOSE; else if (hasWon) state = GameState::WIN;`).
   - **Verification/Change:** Tested by letting timer expire right on the exit rectangle and confirmed `GAME OVER` (`LOSE`) is displayed.
3. **Assistance Requested:** Asked for clean Raylib screen clamping math so the player circle never overlaps the top status bar (`hudHeight`).
   - **Code/Decision Affected:** `Player.cpp` (`Player::ClampToPlayableArea()`).
   - **Verification/Change:** Moved player to the top edge (`y = 56 + radius`) and verified zero overlap with the HUD bar.
