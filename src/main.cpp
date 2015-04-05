#include "gb.h"
#include "texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <chrono>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 576;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Texture* gTexture = NULL;


Gameboy gb;

bool init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "GameBoy Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				gTexture = new Texture(gRenderer);
				gTexture->createBlank(160,144);
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				SDL_RenderPresent( gRenderer );

				SDL_Delay(500);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;

}

bool loadMedia() {
	return true;
}

void close() {
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	delete gTexture;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[]) {

	auto start_time = std::chrono::high_resolution_clock::now();

	if(!init()) {
		printf( "SDL failed to initialize.\n" );
		return -1;
	}

  if(!gb.initialize(false, gTexture)) {
		printf("Gameboy failed to initialize.\n");
		return -2;
	}

	if(argc >= 2) {
		if(!gb.loadGame(argv[1])) {
			printf("Failed to load ROM.\n");
			return -3;
		}
	}
	else {
		if(!gb.loadGame("roms/Tetris.gb")) {
			printf("Failed to load ROM\n");
			return -3;
		}
	}


  auto end_time = std::chrono::high_resolution_clock::now();
  auto time = end_time - start_time;
  std::cout << "Took " <<
    std::chrono::duration_cast<std::chrono::microseconds>(time).count() << "μs to start up.\n";

  unsigned long delta = 0;
	bool quit = false;
	SDL_Event e;

	//int FPS = 60;

	while(!quit) {
		start_time = std::chrono::high_resolution_clock::now();
		//unsigned int start_t = SDL_GetTicks();
		
		if(!gb.emulateCycle(delta)) {
			printf("Gameboy stopped or halted.\n");
			quit = true;
		}

		if(gb.drawFlag) {
			//printf("Screen Draw\n");
			SDL_RenderClear( gRenderer );
			gTexture->render(0,0);
			SDL_RenderPresent( gRenderer );
		}
		
		while(SDL_PollEvent(&e) != 0) {
			if(e.type == SDL_QUIT) {
				quit = true;
			}
		}

		end_time = std::chrono::high_resolution_clock::now();
		time = end_time - start_time;
		delta = std::chrono::duration_cast<std::chrono::microseconds>(time).count();

	}

	close();
	return 0;
}
