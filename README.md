# 🎮 2D Retro Engine

A **2D engine written in C++/OpenGL** to create and play retro-style games (Pang, Bomberman, etc.).  
Includes a demo level, main menu, and credits.  
Feel free to use this code and resources as a base for your own projects!

---

## 🛠️ Features

- ⚡ **Engine**: C++ with OpenGL
  - Uses [GLFW](https://www.glfw.org/) for windows/input
  - [GLEW](http://glew.sourceforge.net/) for OpenGL extensions
  - [GLM](https://glm.g-truc.net/0.9.9/index.html) for math
- 🌠 **Sprites & Animations**  
  Animated sprites for characters and objects (`assets/images/`).
- 🗺️ **Tilemap & Objects**  
  `TileMap` loads level data and manages dynamic/static objects.  
  Includes breakable/unbreakable blocks.
- 🌳 **Quadtree Collisions**  
  Fast collision detection with a quadtree (`Quadtree.h`).
- 🔊 **Audio**  
  `AudioManager` with [miniaudio](https://github.com/mackron/miniaudio) for effects/music (`assets/audio/`).
- 🖥️ **Scenes System**  
  Switch dynamically between Menu, Credits, and Level1 (add more easily).
- 🅰️ **UI & Text**  
  `UIManager` renders text using [FreeType](https://freetype.org/) and arcade fonts (PixelifySans, PressStart2P, Silkscreen, VT323).
- ⚙️ **Central Config**  
  `Config.h` for window sizes, asset paths, constants.

---

## 📁 Project Structure

```
/Engine
    Engine.sln  ->  Visual Studio Solution
    /Engine     ->  Engine source code and sample
    /assets     ->  Images, fonts, audio, and shaders
    /libs       ->  Dependencies (GLFW, GLEW, GLM, SOIL, miniaudio, FreeType)
```

---

## 🖥️ Requirements

- Visual Studio 2019 or newer (**Windows only**)
- All libraries included in `/Engine/libs`  
  (No extra installation needed)
- **Win32 (32-bit) build configuration is recommended** (matches provided libraries)

---

## 🏗️ How to Build

1. **Clone or download** this repository
2. Open `Engine/Engine.sln` with Visual Studio
3. Select build config: **Debug** or **Release** + platform **Win32**
4. Build solution (`Build > Build Solution`)
5. Find executable in `Engine/Debug/` or `Engine/Release/`

---

## 🚀 How to Run

- Run the generated binary (`Engine.exe`)
- The main menu will appear; start the game or view credits
- The sample level is ready to play or extend!

---

## 📦 Third-Party Licenses

- **Fonts:**  
  Pixelify Sans, Press Start 2P, Silkscreen, VT323  
  → [Open Font License (OFL)](https://scripts.sil.org/OFL)
- **Libraries:**  
  - GLFW, GLEW, GLM, SOIL — see their licenses in `libs/`
  - miniaudio — public domain or MIT-0 (`miniaudio.h`)
  - FreeType — dual FTL / GPLv2
- **Audio:**  
  `template.mp3` is an example.  
  Replace/verify its license before distribution.

> Check each `/libs/` subdirectory for more licensing info.

---

## 👤 Author

Héctor Núñez Carpio

---

## 📝 License

This project is open source. See individual library folders for their terms.
