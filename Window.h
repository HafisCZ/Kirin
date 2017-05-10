#pragma once

#include <string>

#include <SDL\SDL.h>
#include <GL/glew.h>

namespace Kirin {

	enum WindowFlags {
		INVISIBLE = 0x1,
		FULLSCREEN = 0x2,
		BORDERLESS = 0x4
	};

	class Window
	{
		public:
			Window();
			~Window();

			int create(const std::string& windowName, int screenWidth, int screenHeight, unsigned int windowFlags);
			void swapBuffer();
			int getScreenWidth() { return _screenWidth; };
			int getScreenheight() { return _screenHeight; };
		private:
			SDL_Window *_sdlWindow;
			int _screenWidth, _screenHeight;
	};

}