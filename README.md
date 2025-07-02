# 2D Videogames: Retro Tributes

This project contains a 2D engine written in C++ designed to recreate classic games (Pang, Bomberman, etc.). It includes a demonstration first level with a main menu and credits. The code and resources can be used as a base for other projects.

## Features

- **2D Engine in C++ / OpenGL**  
  Uses GLFW for window creation and input handling, GLEW for OpenGL extensions, and GLM as the math library.

- **Scene System**  
  Implements Menu, Credits, and Level1, with the ability to dynamically load new scenes.

- **Sprites & Animations**  
  The `Sprite` class manages character and object animations. Sprites are defined in `assets/images/`.

- **Tile Map & Objects**  
  `TileMap` loads level data (`LevelData`) and organizes dynamic and static objects. Includes breakable and unbreakable blocks (`BreakableBlock`, `UnbreakableBlock`).

- **Quadtree for Collisions**  
  `Quadtree.h` implements a spatial structure to accelerate collision checks.

- **Audio Management**  
  `AudioManager` uses the miniaudio library to play effects and music (`assets/audio/`).

- **UI & Text**  
  `UIManager` renders on-screen text using FreeType. Several arcade-style fonts are included (PixelifySans, PressStart2P, Silkscreen, VT323).

- **Centralized Configuration**  
  `Config.h` defines window sizes, asset paths, and other game constants.

## Repository Structure
```
/Engine
    Engine.sln  ->  Visual Studio Solution
    /Engine     ->  Engine source code and sample
    /assets     ->  Images, fonts, audio, and shaders
    /libs       ->  Dependencies (GLFW, GLEW, GLM, SOIL, miniaudio, FreeType)
```

## Requirements

- Visual Studio 2019 or newer (project designed for Windows).
- External libraries are already included under `Engine/libs`, so no separate installation is required.
- It is recommended to use the 32-bit configuration (Win32) to match the provided libraries.

## Build Instructions

1. Clone or download this repository.
2. Open `Engine/Engine.sln` with Visual Studio.
3. Select the desired configuration (Debug or Release) and platform (Win32).
4. Build the solution (**Build > Build Solution**). An executable will be generated in `Engine/Debug/` or `Engine/Release/`.

## Running the Game

After building, run the generated binary (`Engine.exe`).  
The main menu will appear, allowing you to start the game or view the credits. An example level is included as a base for future games.

## Third-party Licenses

- **Fonts**: Pixelify Sans, Press Start 2P, Silkscreen, and VT323 are from Google Fonts and licensed under the [OFL (Open Font License)](https://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=OFL).
- **Libraries**:
    - GLFW, GLEW, GLM, SOIL: under their respective licenses (see subdirectories in `libs/`).
    - miniaudio: public domain or MIT-0 (see miniaudio.h header).
    - FreeType: dual license FTL / GPLv2.
- **Audio**: `template.mp3` is included as a sample. Replace or verify its license before distributing your game.

Refer to the license files in each subdirectory for more details.
