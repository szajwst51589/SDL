#include "SDL.h"
#include "utility.h"
#include "game.h"
#include <iostream>

using namespace std;


void SDLInit() {
	if(SDL_WasInit(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Init error: SDL is already running." << std::endl;
		return;
	}
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		throw SDL_GetError();
	}
	std::cout << "Init SDL successfully." << std::endl;
}

void SDLQuit() {
	if(SDL_WasInit(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Quit error: SDL is not running." << std::endl;
		return;
	}
	SDL_Quit();
	std::cout << "Quit SDL successfully." << std::endl;
}

int main (int argc, char** argv) {

	try {
		SDLInit();
	} catch(const char* s) {
		std::cerr << s << std::endl;
		return -1;
	}

	Game* g = new Game();
	g->update();

	atexit(SDLQuit);
	return 0;
}