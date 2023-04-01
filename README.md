# Langtons-Ant
This is a simple implementation of Langton's Ant using C++ and SDL2.

## Description
Langton's Ant is a cellular automaton that was invented by Chris Langton in 1986. It is a simple example of how complex behavior can arise from simple rules. The simulation consists of an ant moving on a grid of cells. Each cell can be in one of two states, black or white. The ant follows the following rules:
* If the ant is on a white cell, it turns 90 degrees to the right, changes the cell to black, and moves forward one cell.
* If the ant is on a black cell, it turns 90 degrees to the left, changes the cell to white, and moves forward one cell.
With these simple rules, the ant's movement can become chaotic and unpredictable.

<p align="center">
  <img src="https://user-images.githubusercontent.com/72578289/229261245-a8bba735-b108-4529-bd11-b94e30ca0db0.PNG" alt="Langton's Ant">
</p>

## Requirements
C++ compiler (supporting C++17)
SDL2 library

## Installation
1. Clone this repository to your local machine using git clone https://github.com/yourusername/langtons-ant.git.
2. Install the SDL2 library on your system. Instructions for different operating systems can be found on the [SDL website](https://github.com/libsdl-org/SDL/releases/tag/release-2.26.4).
3. Navigate to the cloned directory and compile the source code using the command g++ -std=c++17 -o langtons_ant main.cpp -lSDL2.
4. Run the program using the command ./langtons_ant.

## Usage
When the program is running, you can use the following keys to control the simulation:
* Up: Increase Ant Speed.
* Down: Decrease Ant Speed.

## Credits
This project was created by Christopher Tscheschlog. It is licensed under the MIT License.
