# PkmBoy - v0.0.1 - WIP

## Introduction
This humble project is just a 2D engine written in C++, using [SDL2](https://www.libsdl.org/index.php) (Simple Direct Layer) with the idea in mind of recreating an enviroment similar to the Pokemon Red and Blue from the Gameboy console. It's obvious that we are way ahead of the time technologycally, since the game was launched. So many of the rules or limitation I'm taking into consideration in this project, are more an aesthetical decision rather than a limitation of any reason.
 
## Visual Guidelines
The starting point to achieve this "Old Pokemon nostalgia" is to imitate the **look and feel** from the old games and then add it to this engine. For that reason, I'll try to number some of the UI and visual guidelines that I've found in the Internet, in order to achieve a similar feel like playing a Pokemon Blue/Red. Many of them are actually based on the old system's hardware limitations, and other were decisions that the Pokemon's developers choose in order to create the games aesthetics.

### Display Resolution and limitations
The original Gameboy display resolution was 160px(width) per 144px(tall), and the game was mostly composed of 20 * 18 Grid or 8px per 8px Tiles.
As the Gameboy console doesn't have a "frame buffer", you can't specify the color of each pixel on screen individually. Because of that, all the on-screen images are built by assembling loads of "tiles", i.e. 8x8 pixels squares. This is applicable for both background and sprites:

- The Sprites can work using 4 8x8px tiles, measuring 16x16px, but also the Gameboy could make a 8x16 display mode for the sprites (meaning, 2 tiles of 8x16px).
- 8px per 8px repetitive tiles for floors.
- Max number of tiles in tilemap: 384 (with some nasty tricks), 256 (w/o nasty tricks)
- Colors: Gameboy supports a 4 colors pallete: Black, Darkgrey, Lightgrey and White. 
- limit to 40 sprites onscreen,
- the Game Boy can't display more than 10 sprites on the same line
- the Game Boy VRAM is limited (8KB), and it can store only 256 different tiles at a specific moment.

To be usable in HDPI screens, the Engine will suppport an "scaling" factor to make the tiles and sprites bigger.

### Graphics Layers
- 3 Layers & colors options:
* Background layer: it supports 4 colors, 32x32 grid of 8x8 tiles, scrollable, and scrolling wraps
* Sprite layer: it supports 3 colors, and a transparent background for sprites.
There are actually two possible Sprites "color modes" : one with the Black and no White, and other with White and no Black (but the in-between colors are always there). 
* "Interface" layer: usually its use is to show a Menu, always on top of the others two layers (non transparent).

### Visual aspects and design
- Mostly all objects/sprites desings are going to be multiples of 8. So you could create a "table" of 24x32 pixels, or a bed of 32*16 pixels. Characters sprites are mostly 16X16 pixels, and this Engine implementation will be mostly set around that values (Meaning that objects, colliders and so will be related to this measure). 

Sources:
- [Sprite Analysis: Top-Down RPG Pixel Art Pokémon](https://www.youtube.com/watch?v=gwF0L55kIgg)
- [Making a Game Boy game in 2017](https://www.gamasutra.com/blogs/DoctorLudos/20171207/311143/Making_a_Game_Boy_game_in_2017_A_quotSheep_It_Upquot_PostMortem_part_12.php)
- [https://itch.io/jam/gbjam-5/topic/41384/the-actual-gb-limits](https://itch.io/jam/gbjam-5/topic/41384/the-actual-gb-limits)

## Engine Specs

## Installation and Dependencies

### Dependencies
The Game is built using the [SDL2](https://www.libsdl.org/index.php) library, for managing graphics, input and output, and more. In order to compile and work with the code, you need to have the developer version of some SDL2 libraries:
- [SDL2 development Libraries](https://www.libsdl.org/download-2.0.php)
- [SDL2 Image](https://www.libsdl.org/projects/SDL_image/) 
- [SDL_ttf 2](https://www.libsdl.org/projects/SDL_ttf/)

#### Windows
I've installed the SDL2 libraries using [vcpkg](https://github.com/microsoft/vcpkg)

### MacOS
I've installed the SDL2 librarys using [Brew](https://brew.sh/)

### Compile and run
The application build process is made using [CMAKE](https://cmake.org/), which allows to have different output system targets:
- Linux
- macOS
- Windows (x86 & x64)

#### Linux
```
cmake -S . -B out/build # This will compile the source code files
cmake --build out/build # Link the source files
```

#### macOS
```
cmake -S . -B out/build # This will compile the source code files
cmake --build out/build # Link the source files
```

#### Windows
I've been using Visual Studio 2019 Community, that should detect the CMAKE configs. You could download both x86 and x64 SDL libraries (using vcpkg) and the set the Debug-x86 or Debug-x64 within VS2019. Then, you have to first create the CMAKE cache, set `main.cpp` as the project's start poing and finally run the app (which should finish the compilation process).
You can debug the app using VS2019. 
