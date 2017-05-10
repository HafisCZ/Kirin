#include "Window.h"
#include "Errors.h"

namespace Kirin {

	Window::Window() {

	}


	Window::~Window() {

	}

	int Window::create(const std::string& windowName, int screenWidth, int screenHeight, unsigned int windowFlags) {
		// Set dimensions
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;

		// Set window flags
		Uint32 flags = SDL_WINDOW_OPENGL;
		if (windowFlags & INVISIBLE) flags |= SDL_WINDOW_HIDDEN;
		if (windowFlags & FULLSCREEN) flags |= SDL_WINDOW_FULLSCREEN;
		if (windowFlags & BORDERLESS) flags |= SDL_WINDOW_BORDERLESS;

		// Create new window
		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
		if (_sdlWindow == nullptr) Kirin::fatalError("SDL Window could not be created!");

		// Create content in window
		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (glContext == nullptr) Kirin::fatalError("SDL_GL context could not be created!");

		// Init GLEW
		GLenum error = glewInit();
		if (error != GLEW_OK) Kirin::fatalError("Could not initialize glew!");

		// Print out OpenGL version
		std::printf("[OpenGL Version] %s\n", glGetString(GL_VERSION));

		// Set window background color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// Set VSYNC
		SDL_GL_SetSwapInterval(0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::swapBuffer() {
		SDL_GL_SwapWindow(_sdlWindow);
	}

}