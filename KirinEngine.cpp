#include <SDL\SDL.h>
#include <GL\glew.h>

#include "KirinEngine.h"

namespace Kirin {

	int init()
	{
		// Initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		// Set double buffer on
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}

}