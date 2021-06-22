#include <iostream>
#include <SDL.h> 
#include <SDL_ttf.h>
#include <string>
#include "CustomRenderer.h"

using namespace std;
SDL_Window* window; 
SDL_Renderer* renderer;
CustomRenderer* customRenderer;

int main(int argc, char* argv[]) 
{ 
	cout << "start\n";
	// Initialize SDL 
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{ 
		printf("Could not initialize SDL! (%s)\n", SDL_GetError());
		return -1;
	} 
	TTF_Init();
	// Create window 
	window = SDL_CreateWindow("GOMOK AI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 700, 700, SDL_WINDOW_OPENGL); 
	if (window == NULL) 
	{ 
		printf("Could not create window! (%s)\n", SDL_GetError());
		return -1; 
	} 
	// Create renderer 
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_TARGETTEXTURE);
	if (renderer == NULL) 
	{ 
		printf("Could not create renderer! (%s)\n", SDL_GetError());
		return -1; 
	} 
	customRenderer = new CustomRenderer(renderer);
	
	// Clear renderer (white) 
	customRenderer->DrawColorChange({ 255,255,255,0 });
	customRenderer->ClearRenderer();
	// Draw rect (red) 

	customRenderer->DrawColorChange({ 255,0,0,0 });
	customRenderer->DrawRect(50, 50, 100, 100);
	// Draw circle
	customRenderer->DrawEmptyCircle(100, 100, 100);

	//DrawFilledCircle(renderer, { 0,0,255 }, 300, 100, 100);
	customRenderer->DrawFilledCircle(300, 100, 100);
	// Draw line
	customRenderer->DrawLine(320, 200, 300, 240);
	// Draw text
	string message = "¤¾¤·¿°";
	customRenderer->DrawText(message, 20, 20, 15, { 255,255,0,0 });
	// Update screen 
	customRenderer->Render();
	
	SDL_Event event; 
	int done = 0; 
	while (!done) 
	{ 
		SDL_PollEvent(&event); 
		if (event.type == SDL_QUIT) 
		{ 
			done = 1; 
		} 
	} 
	
	SDL_DestroyRenderer(renderer); 
	SDL_DestroyWindow(window); 
	SDL_Quit();
	TTF_Quit();
	printf("End\n"); 
	return 0; 
}
