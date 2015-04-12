#include "gb.h"
#include "texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <exception>
#include <string>
#include <unordered_map>

class Debug {
	public:
		Gameboy* gb = NULL;
		GameboyGPU* gpu = NULL;
		bool init(Gameboy* gameboy) {
			gb = gameboy;
			gpu = gb->gpu;
		}

		void dumpVRAM() {
			std::ofstream dump;
			dump.open("dumps/vram.bin", std::ios::binary);
			for(int i=0;i<gpu->vram.size();i++) {
				dump << gpu->vram[i];
			}
			dump.close();
		}

		void dumpOAM() {
			std::ofstream dump;
			dump.open("dumps/oam.bin", std::ios::binary);
			for(int i=0;i<gpu->oam.size();i++) {
				dump << gpu->oam[i];
			}
			dump.close();
		}

		void dumpTiles() {
			std::ofstream dump;
			dump.open("dumps/tiles.txt", std::ios::binary);
			for(int i=0;i<gpu->tiles.size();i++) {
				for(int j=0; j<gpu->tiles[i].size(); j++) {
					dump << (char)(gpu->tiles[i][j] + 48);
					if((j+1)%8==0) 
						dump << "\n";
				}
				dump << "\n\n";
			}
			dump.close();
		}

		void dumpRegs() {
			std::ofstream dump;
			dump.open("dumps/regs.bin", std::ios::binary);
			for(int i=0;i<gpu->regs.size();i++) {
				dump << gpu->regs[i];
			}
			dump.close();
		}

		void dumpScreen() {
			std::ofstream dump;
			dump.open("dumps/screen.bin", std::ios::binary);
			for(int i=0;i<gpu->screen.size();i++) {
				dump << gpu->screen[i];
			}
			dump.close();
		}

};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 576;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Texture* gTexture = NULL;
Debug dbg;


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
	std::unordered_map<SDL_Keycode ,Gameboy::GB_KEYS> keyMap;
	keyMap = {{SDLK_z, Gameboy::GB_A}, {SDLK_x, Gameboy::GB_B}, {SDLK_UP, Gameboy::GB_UP}, {SDLK_DOWN, Gameboy::GB_DOWN}, 
		{SDLK_LEFT, Gameboy::GB_LEFT}, {SDLK_RIGHT, Gameboy::GB_RIGHT}, {SDLK_RETURN, Gameboy::GB_START}, {SDLK_RSHIFT, Gameboy::GB_SELECT}};

	std::array<bool, 8> keyStates;
	keyStates = {false, false, false, false, false, false, false, false};

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
		if(!gb.loadGame("roms/opus5.gb")) {
			printf("Failed to load ROM\n");
			return -3;
		}
	}

	dbg.init(&gb);


  auto end_time = std::chrono::high_resolution_clock::now();
  auto time = end_time - start_time;
  std::cout << "Took " <<
    std::chrono::duration_cast<std::chrono::microseconds>(time).count() << "μs to start up.\n";

  unsigned long delta = 0;
	bool quit = false;
	bool pause = false;
	bool step = false;
	SDL_Event e;

	//int FPS = 60;

	while(!quit) {
		start_time = std::chrono::high_resolution_clock::now();
		//unsigned int start_t = SDL_GetTicks();
		
		if(!pause || step) {
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
			step = false;
		}
		
		while(SDL_PollEvent(&e) != 0) {
			switch(e.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					try {
						Gameboy::GB_KEYS key = keyMap.at(e.key.keysym.sym);
						keyStates.at(key) = true;
					}
					catch(std::exception& e) {
						printf("%s\n", e.what());
					}
					switch(e.key.keysym.sym) {
						case SDLK_p:
							pause = !pause;
							break;
						case SDLK_h:
							dbg.dumpVRAM();
							break;
						case SDLK_j:
							dbg.dumpOAM();
							break;
						case SDLK_k:
							dbg.dumpScreen();
							break;
						case SDLK_l:
							dbg.dumpRegs();
							break;
						case SDLK_t:
							dbg.dumpTiles();
							break;
						case SDLK_n:
							step = true;
							break;
					}
					break;
				case SDL_KEYUP:
					try {
						Gameboy::GB_KEYS key = keyMap.at(e.key.keysym.sym);
						keyStates.at(key) = false;
					}
					catch(std::exception& e) {
						printf("%s\n", e.what());
					}
					break;
			}
		}
		gb.getKeys(keyStates);

		if(pause)
    {
      SDL_Delay(32); //Yay stable framerate!
    }

		end_time = std::chrono::high_resolution_clock::now();
		time = end_time - start_time;
		delta = std::chrono::duration_cast<std::chrono::microseconds>(time).count();

	}

	close();
	return 0;
}
