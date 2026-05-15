# Xonix Game 🎮

A C++ implementation of the classic **Xonix** arcade game built with **SFML 2.x**.

Capture territory by drawing lines across the grid while avoiding enemies. The more tiles you capture, the higher your score!

---

## Features

- Classic Xonix gameplay on a 40×25 grid
- Enemy collision detection
- Pause/resume functionality
- Score tracking with Top 5 leaderboard saved to `scores.txt`
- Custom fonts and images
- Main menu and pause menu

---

## Requirements

- **C++17** or later
- **CMake 3.10+**
- **SFML 2.5+**

---

## Installation & Build

### Linux / WSL (Parrot OS, Ubuntu, Debian)

**1. Install dependencies**
```bash
sudo apt update
sudo apt install g++ cmake make libsfml-dev -y
```

**2. Clone the repository**
```bash
git clone https://github.com/Basitx56/xonix.git
cd xonix
```

**3. Build the game**
```bash
mkdir build && cd build
cmake ..
make
```

**4. Run the game**
```bash
./xonix
```

---

## Controls

| Key | Action |
|-----|--------|
| Arrow Keys | Move player |
| `P` | Pause / Resume |
| `Esc` | Quit |

---

## Project Structure

```
xonix/
├── main.cpp          # Core game logic
├── main.h            # Game headers
├── Menu.cpp          # Menu system
├── Menu.h            # Menu headers
├── CMakeLists.txt    # Build configuration
├── images/           # Game assets
└── Fonts/            # Font files
```

---

## How to Play

1. Move your player across the open area to draw lines
2. Connect both ends of a line back to the border to capture territory
3. Avoid enemies — if they touch your trail, you lose a life
4. Capture as much territory as possible to maximize your score

---

## Built With

- [SFML](https://www.sfml-dev.org/) - Simple and Fast Multimedia Library
- C++17
- CMake