# Classy-Clash

## Introduction

**Classy-Clash** is a 2D tile-based game prototype written in C++ using the raylib library. The project is inspired by a course on C++ game development and uses external assets and a map editor to build a simple world for exploring and gameplay.  

The goal of this project is to practise object-oriented programming (OOP) in C++, to learn how to combine C++ game logic with tile-based rendering, and to build a small playable environment using freely available assets and map designs.

---

## Motivation & Background

- The codebase follows (and extends) lessons from the course GameDev.tv C++ Fundamentals: Game Programming For Beginners. :contentReference[oaicite:2]{index=2}  
- I use raylib for rendering and input, and standard C++ for game logic, classes, inheritance, and entity management.  
- For level design, I rely on Tiled — a free and open-source 2D tile map editor — to create maps. :contentReference[oaicite:4]{index=4}  
- The visual assets (tileset) come from a free pack obtained from Itch.io: *“RPG Nature Tileset”*.  

---

## Table of Contents

- [Installation](#installation)  
- [Usage](#usage)  
- [Features](#features)  
- [Project Structure](#project-structure)  
- [Assets & Credits](#assets--credits)  
- [Building / Running](#building--running)  
- [Dependencies](#dependencies)  
- [Configuration](#configuration)  
- [Future Work](#future-work)  
- [License & Disclaimer](#license--disclaimer)  

---

## Installation

**Prerequisites**  
- A C++ compiler (e.g. g++, clang, or MSVC) supporting C++11 or newer.  
- raylib library installed (with proper include and link paths).  
- A tool to build — the project includes a `Makefile`.  

**Steps**  
1. Clone this repo:  
   ```bash
   git clone https://github.com/YimingCao-Eric/Classy-Clash.git
2. Ensure raylib is installed on your system.

3. From the project root, run:
    ```bash
    make
4. Run the compiled executable (e.g. ./classy-clash on Linux/macOS, or the .exe on Windows).

---

## Usage

Once the game is built and executed, the program will open a window and load the tile map designed with Tiled. The player can navigate (movement depends on the implementation) and interact with the scene.

You can modify or replace the .tmx map file (or tileset) to test different maps or extend the world.

Features

Object-oriented C++ code: base classes, inheritance for characters/enemies/props.

Tile-based world rendering using raylib — tilesets loaded from a sprite sheet.

Map editing via Tiled: supports defining terrain, positioning props, and layering.

Simple entity system: characters, props, enemies — modular and extendable.

Easily replaceable assets: you can swap tilesets or map files, thanks to flexible asset loading.

Project Structure
/ (project root)
├── characters/         # code for characters (player, enemy, etc.)
│   ├── BaseCharacter.h / .cpp
│   ├── Character.h / .cpp
│   └── Enemy.h / .cpp
├── nature_tileset/     # the tileset graphics downloaded from Itch.io
├── Prop.h / Prop.cpp   # props / environment objects
├── main.cpp            # main entry point
├── Makefile            # build script
└── …                   # other source files

Assets & Credits

Tile graphics: RPG Nature Tileset from Itch.io (free)

Map editor: Tiled (map files) 
doc.mapeditor.org
+1

Game engine / rendering: raylib

If you use or distribute this project (or a fork), please keep the original asset credit, and link back to where you downloaded the tileset. This is standard practice when using free assets from sites like Itch.io. Many developers credit assets in a text file or in-game credits screen. 
Reddit
+1

Building / Running

To build:

make


To run (on Unix-like systems):

./classy-clash


On Windows, double-click the .exe produced or run it from command line.

Dependencies

raylib (graphics, input, window)

C++ standard library

Configuration

Map files / tilesets: you can replace files under nature_tileset/ or load new .tmx maps created with Tiled.

Build flags: edited via Makefile.