# 🧙‍♂️ C++ Monster Adventure Game

A simple text-based adventure game written in **modern C++17**, where you (the player) battle randomly generated monsters, gain levels, and collect gold. The game ends when you either die or reach level 20.

---

## 🎮 Gameplay Overview

- You start as a player with:
  - 10 health points  
  - 1 attack damage  
  - 0 gold  
  - Level 1  

- During each round, you **encounter a random monster**:
  - `dragon` 🐉 (strongest)
  - `orc` ⚔️ (medium)
  - `slime` 💧 (weak)

- You can choose to:
  - **Fight (F/f)** – attack the monster and risk taking damage.
  - **Run (R/r)** – attempt to flee; success is 50/50. If you fail, the monster attacks.

- Killing a monster grants:
  - Level up (+1 level, +1 damage)
  - The monster’s gold

- You **win** if you reach **level 20**,  
  or **lose** if your health drops to 0.

---

## ⚙️ How It Works

### Key Classes

| Class | Description |
|--------|-------------|
| `Creature` | Base class for all entities (Player & Monster) — handles health, damage, gold, etc. |
| `Player` | Inherits from `Creature`. Tracks level and winning condition. |
| `Monster` | Inherits from `Creature`. Contains static monster templates and a random generator for encounters. |

---

### Random Number Generation

Uses C++ `<random>` library for high-quality random numbers:
```cpp
static random_device rd;
static mt19937 gen(rd());
uniform_int_distribution<int> dist(0, max_types - 1);
