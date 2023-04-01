//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <stdio.h>
#include <array>
#include <windows.h>

// Factor Dimensions
const int dimen = 2;

// Square Screen
const int SCREEN_SIZE = 800;

// Screen dimension constants
const int SCREEN_WIDTH = SCREEN_SIZE;
const int SCREEN_HEIGHT = SCREEN_SIZE;

// Grid's Max rows and columns
const int ROWS = SCREEN_WIDTH / dimen;
const int COLS = SCREEN_HEIGHT / dimen;

// Ant initial Coordinates
int xPos = ROWS / 2;
int yPos = COLS / 2;

// Ant directions left: 0, up: 1, right: 2, down: 3
int antDirection = 0;

// Control Render Speed (Sleep Delay)
int speed = 5;

// Starts up SDL and creates window
bool init();

// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The window renderer
SDL_Renderer* gRenderer = NULL;

// Create grid
std::array<std::array<bool, ROWS>, COLS> grid;

void drawCells() {
	// Render Cells
	for (int y = 0; y < COLS; y++) {
		for (int x = 0; x < ROWS; x++) {
			// { x, y, width, height }
			if (grid[y][x]) {
				SDL_Rect fillRect = { (x * dimen), (y * dimen), dimen, dimen };
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
				SDL_RenderFillRect(gRenderer, &fillRect);
			}
		}
	}
}

// True -> Clockwise, False -> Counter-Clockwise
void changeAntDirection(bool clockwise) {

	// +1 -> Clockwise 
	// -1 -> Counter-Clockwise
	if (clockwise)
		antDirection = (antDirection + 1) % 4;
	else
		antDirection = antDirection != 0 ? antDirection - 1 : 3;

}

void moveAnt() {
	/*
		At a white square, turn 90° clockwise, flip the color of the square, move forward one unit
		At a black square, turn 90° counter-clockwise, flip the color of the square, move forward one unit
	*/

	// The cell the ant is on is black
	if (grid[yPos][xPos]) {
		changeAntDirection(false);
	}
	// The cell the ant is on is white
	else {
		changeAntDirection(true);
	}

	// Flip the cell that the ant is on
	grid[yPos][xPos] = !grid[yPos][xPos];

	// Move the ant in the direction it is facing
	switch (antDirection) {

		// Left
		case 0:
			xPos = xPos > 0 ? xPos - 1 : ROWS - 1;
			break;
		// Up
		case 1:
			yPos = yPos > 0 ? yPos - 1 : COLS - 1;
			break;
		// Right
		case 2:
			xPos = xPos < ROWS - 1 ? xPos + 1 : 0;
			break;
		// Down
		case 3:
			yPos = yPos < COLS - 1 ? yPos + 1 : 0;
			break;
	}

}
void drawAnt() {

	// Create the Ant Rect
	SDL_Rect fillRect = { (xPos * dimen + (dimen/4)), (yPos * dimen + (dimen / 4)), (dimen / 2), (dimen / 2) };

	// Red Ant 
	SDL_SetRenderDrawColor(gRenderer, 0xF0, 0x00, 0x00, 0x00);
	SDL_RenderFillRect(gRenderer, &fillRect);
}

// Create the grid 
void initGrid() {
	for (int y = 0; y < COLS; y++) {
		for (int x = 0; x < ROWS; x++) {
			
			// Init to white
			grid[y][x] = false;

		}

	}
}

bool init()
{
	// Init Grid
	initGrid();

	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create window
		gWindow = SDL_CreateWindow("Langton's Ant", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

			}
		}
	}

	return success;
}


void close()
{
	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[])
{
	// Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		// Main loop flag
		bool quit = false;

		// Event handler
		SDL_Event e;

		// While application is running
		while (!quit)
		{
			Uint64 start = SDL_GetPerformanceCounter();

			// Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				// User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}
			// Get the state of each key on the keyboard
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

			// Exit on escape press
			if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {
				quit = true;
			}
			// When up pressed, decrease wait-time between rendering
			else if (currentKeyStates[SDL_SCANCODE_UP]) {
				if (speed != 0)
					speed -= 1;
			}
			// When down pressed, increase wait-time between rendering
			else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
				if (speed < 100)
					speed += 1;
			}

			// Clear screen
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			// Render Cells
			drawCells();

			// Render Ant
			drawAnt();

			// Move Ant
			moveAnt();

			// Update screen
			SDL_RenderPresent(gRenderer);
			Sleep(speed);
		}
	}

	// Free resources and close SDL
	close();

	return 0;
}