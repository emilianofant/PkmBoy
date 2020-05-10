# PkmBoy

## Introduction
This humble project is just a 2D engine written in C++, using SDL2 with the idea in mind of recreating an enviroment similar to the Pokemon Red and Blue from the Gameboy console. It's obvious that we are technologycally speaking way ahead of the time the game was launched, so many of the rules or limitation I'm including in this project, are more of an aesthetical decision rather than a limitation of any reason.

## Visual Guidelines
The main starting point to achieve this "Old Pokemon nostalgia" is the **look and feel** that you could add to the game. For that reason, I'll try to number some of the UI and visual guidelines that I could cover in order to achieve a similar feel like playing a Pokemon Blue/Red. Many of them are actually based on the old system limitations, and other were decisions that de Pokemon's developers choose in order to create the games.

### Display Resolution
The original Gameboy display resolution was 160px(width) per 144px(tall), and the game was mostly composed of 20 * 18 Grid or 8px per 8px Tiles.

- Mostly all objects/sprites are going to be multiples of 8. So you could create a table of 24x32 pixels, or a bed of 32*16 pixels. Characters sprites are mostly 16X16 pixels, and this Engine implementation will be mostly set around that values (Meaning that objects, colliders and so will be related to this measure). 
- 8px per 8px repetitive tiles for floors.

Sources:
- [Sprite Analysis: Top-Down RPG Pixel Art (Pokémon)](git remote add origin git@github.com:emilianofant/PkmBoy.git
git push -u origin master)

## Engine Specs
