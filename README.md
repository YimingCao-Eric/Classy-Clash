# Classy Clash

A top-down action game built with C++ and Raylib, featuring a knight character fighting against enemies in a 2D world.

## Overview

Classy Clash is a simple but engaging top-down action game where you play as a knight navigating through a world filled with enemies and obstacles. The game features real-time combat, enemy AI, collision detection, and a health system.

## Motivation & Background

- The codebase follows (and extends) lessons from the course GameDev.tv [C++ Fundamentals: Game Programming For Beginners](https://www.udemy.com/course/cpp-fundamentals/).   
- I use raylib for rendering and input, and standard C++ for game logic, classes, inheritance, and entity management.  
- For level design, I rely on [Tiled](https://thorbjorn.itch.io/tiled) — a free and open-source 2D tile map editor — to create maps. 
- The visual assets (tileset) come from a free pack obtained from Itch.io: *[“RPG Nature Tileset”](https://stealthix.itch.io/rpg-nature-tileset)*.  

## Features

- **Player Character**: Play as a knight with smooth movement and animations
- **Enemy AI**: Enemies automatically chase the player and deal damage on contact
- **Combat System**: Attack enemies with your sword using mouse clicks
- **Health System**: Track your health and avoid dying from enemy attacks
- **Collision Detection**: Navigate around props and stay within map boundaries
- **Sprite Animations**: Idle and running animations for all characters
- **Camera System**: Camera follows the player character

## Requirements

### Dependencies

- **Raylib**: Graphics library (version 3.0.0 or compatible)
- **C++ Compiler**: 
  - Windows: MinGW-w64 (g++)
  - Linux: GCC (g++)
  - macOS: Clang++

### System Requirements

- Windows, Linux, or macOS
- OpenGL support

## Building the Project

### Windows

1. Ensure you have Raylib installed and the path configured in the Makefile
2. Open a terminal in the project directory
3. Run:
   ```bash
   mingw32-make
   ```

### Linux

1. Install Raylib development libraries:
   ```bash
   sudo apt-get install libraylib-dev  # Debian/Ubuntu
   ```
2. Build the project:
   ```bash
   make
   ```

### macOS

1. Install Raylib via Homebrew:
   ```bash
   brew install raylib
   ```
2. Build the project:
   ```bash
   make
   ```

### Build Configuration

The Makefile supports the following build modes:
- **RELEASE** (default): Optimized build
- **DEBUG**: Debug build with symbols

To build in debug mode:
```bash
make BUILD_MODE=DEBUG
```

## Running the Game

After building, run the executable:

- **Windows**: `game.exe` or `main.exe`
- **Linux/macOS**: `./game` or `./main`

Make sure the following asset directories are present in the same directory as the executable:
- `characters/` - Character sprites
- `nature_tileset/` - Map and prop textures

## Controls

- **W** - Move up
- **A** - Move left
- **S** - Move down
- **D** - Move right
- **Left Mouse Button** - Attack with sword
- **Close Window** - Exit game

## Game Mechanics

### Player (Knight)

- Starts with 100 health
- Movement speed: 4 pixels per frame
- Can attack enemies with a sword
- Health decreases when in contact with enemies
- Dies when health reaches 0

### Enemies

- **Goblin**: Spawns at position (500, 700)
- **Slime**: Spawns at position (800, 100)
- Automatically chase the player
- Deal 10 damage per second when in contact
- Stop moving when within 25 pixels of the player
- Can be killed by sword attacks

### Props

- Static objects (rocks) that block movement
- Two rocks placed at positions (600, 300) and (400, 500)
- Collision detection prevents player from walking through them

### Map

- World map loaded from `nature_tileset/OpenWorldMap24x24.png`
- Scaled 4x for display
- Player cannot move outside map boundaries

## Project Structure

```
Classy Clash/
├── main.cpp              # Main game loop and initialization
├── BaseCharacter.h/cpp   # Base class for all characters
├── Character.h/cpp       # Player character implementation
├── Enemy.h/cpp           # Enemy AI and behavior
├── Prop.h/cpp            # Static world objects
├── Makefile              # Build configuration
├── README.md             # This file
├── characters/           # Character sprite assets
│   ├── knight_idle_spritesheet.png
│   ├── knight_run_spritesheet.png
│   ├── goblin_idle_spritesheet.png
│   ├── goblin_run_spritesheet.png
│   ├── slime_idle_spritesheet.png
│   ├── slime_run_spritesheet.png
│   ├── weapon_sword.png
│   └── weapon_sword_1.png
└── nature_tileset/       # Map and environment assets
    ├── OpenWorldMap24x24.png
    ├── Rock.png
    ├── Bush.png
    ├── Log.png
    └── Sign.png
```

## Code Architecture

### Class Hierarchy

- **BaseCharacter**: Abstract base class providing common functionality
  - Animation system (idle/run)
  - Movement and velocity handling
  - Collision detection
  - World position tracking
  
- **Character**: Player character extending BaseCharacter
  - Input handling (WASD)
  - Weapon rendering and collision
  - Health system
  - Screen-centered positioning
  
- **Enemy**: Enemy character extending BaseCharacter
  - AI pathfinding (chases player)
  - Damage dealing on contact
  - Custom textures per enemy type
  
- **Prop**: Static world objects
  - Collision detection
  - Camera-relative rendering

### Key Systems

1. **Animation System**: Frame-based sprite animation with configurable frame rates
2. **Camera System**: Player-centered camera that follows the character
3. **Collision System**: Rectangle-based collision detection for characters, props, and weapons
4. **Combat System**: Weapon collision detection on mouse click

## Assets

All game assets are located in:
- `characters/` - Character spritesheets and weapons
- `nature_tileset/` - Map tiles and environmental props

## Troubleshooting

### Build Issues

- **Raylib not found**: Ensure Raylib is installed and the `RAYLIB_PATH` in the Makefile points to the correct location
- **Missing textures**: Ensure asset directories (`characters/` and `nature_tileset/`) are in the same directory as the executable
- **Linker errors**: Verify that Raylib libraries are properly linked in the Makefile

### Runtime Issues

- **Window doesn't open**: Check that OpenGL drivers are installed
- **Textures not loading**: Verify asset file paths are correct relative to the executable
- **Game runs slowly**: Try building in RELEASE mode for better performance

## License

This project uses Raylib, which is licensed under the zlib/libpng license. See the Makefile for Raylib license information.

## Credits

- **Graphics Library**: [Raylib](https://www.raylib.com/)
- **Game Engine**: Custom C++ implementation using Raylib