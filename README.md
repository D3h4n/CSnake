# CSNAKE

Author: Deshawn Knight
Last Updated: 21/04/2022

## About

- A simple recreation of the classic snake game using WinGDI and PThreads.

## Setup

### Requirements

- A C compiler (I use minGW)
- Optionally make

### Compilation

- Run `make` to use the makefile to build the executable (NOTE: update the CC variable in the makefile to your compiler)

or

- Use your c compiler to compile the `main.c` file including the following flags `-lgdi32 -pthread -std=c99`

## Playing the Game

- Run the snake executable and use the arrow keys or WASD to control the snake
- Try to eat as much fruit as possible without bumping into yourself
- Have fun!! :^)
