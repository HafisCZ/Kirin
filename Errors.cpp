#include "Errors.h"

#include <cstdlib>

#include <iostream>
#include <sdl/SDL.h>

namespace Kirin {

	void fatalError(std::string errorString, int errorCode) {
		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit...";
		std::cin.get();
		SDL_Quit();
		exit(errorCode);
	}

}