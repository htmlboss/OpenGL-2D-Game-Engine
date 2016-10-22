#include "Window.h"

#include "includes\ImageLoader.h"

namespace Engine {

	Window::Window() {

	}

	Window::~Window() {
	}

	int Window::CreateNewWindow(const std::string& windowName, unsigned int windowflags, const std::string& windowIcon) {

		Uint32 flags = SDL_WINDOW_OPENGL;

		if (windowflags& INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (windowflags& FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (windowflags& BORDERLESS) {
			flags |= SDL_WINDOW_BORDERLESS;
		}

		//Open an SDL window
		m_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, static_cast<int>(getScreenWidth()), static_cast<int>(getScreenHeight()), flags);
		
		if (m_sdlWindow == nullptr) {
			fatalError("SDL Window could not be created!");
		}

		//Setup window icon 
		//htps://wiki.libsdl.org/SDL_SetWindowIcon

		Uint16 pixels[16 * 16] = {  // ...or with raw pixel data:
			0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
			0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
			0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
			0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
			0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
			0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
			0x0fff, 0x0aab, 0x0789, 0x0bcc, 0x0eee, 0x09aa, 0x099a, 0x0ddd,
			0x0fff, 0x0eee, 0x0899, 0x0fff, 0x0fff, 0x1fff, 0x0dde, 0x0dee,
			0x0fff, 0xabbc, 0xf779, 0x8cdd, 0x3fff, 0x9bbc, 0xaaab, 0x6fff,
			0x0fff, 0x3fff, 0xbaab, 0x0fff, 0x0fff, 0x6689, 0x6fff, 0x0dee,
			0xe678, 0xf134, 0x8abb, 0xf235, 0xf678, 0xf013, 0xf568, 0xf001,
			0xd889, 0x7abc, 0xf001, 0x0fff, 0x0fff, 0x0bcc, 0x9124, 0x5fff,
			0xf124, 0xf356, 0x3eee, 0x0fff, 0x7bbc, 0xf124, 0x0789, 0x2fff,
			0xf002, 0xd789, 0xf024, 0x0fff, 0x0fff, 0x0002, 0x0134, 0xd79a,
			0x1fff, 0xf023, 0xf000, 0xf124, 0xc99a, 0xf024, 0x0567, 0x0fff,
			0xf002, 0xe678, 0xf013, 0x0fff, 0x0ddd, 0x0fff, 0x0fff, 0xb689,
			0x8abb, 0x0fff, 0x0fff, 0xf001, 0xf235, 0xf013, 0x0fff, 0xd789,
			0xf002, 0x9899, 0xf001, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xe789,
			0xf023, 0xf000, 0xf001, 0xe456, 0x8bcc, 0xf013, 0xf002, 0xf012,
			0x1767, 0x5aaa, 0xf013, 0xf001, 0xf000, 0x0fff, 0x7fff, 0xf124,
			0x0fff, 0x089a, 0x0578, 0x0fff, 0x089a, 0x0013, 0x0245, 0x0eff,
			0x0223, 0x0dde, 0x0135, 0x0789, 0x0ddd, 0xbbbc, 0xf346, 0x0467,
			0x0fff, 0x4eee, 0x3ddd, 0x0edd, 0x0dee, 0x0fff, 0x0fff, 0x0dee,
			0x0def, 0x08ab, 0x0fff, 0x7fff, 0xfabc, 0xf356, 0x0457, 0x0467,
			0x0fff, 0x0bcd, 0x4bde, 0x9bcc, 0x8dee, 0x8eff, 0x8fff, 0x9fff,
			0xadee, 0xeccd, 0xf689, 0xc357, 0x2356, 0x0356, 0x0467, 0x0467,
			0x0fff, 0x0ccd, 0x0bdd, 0x0cdd, 0x0aaa, 0x2234, 0x4135, 0x4346,
			0x5356, 0x2246, 0x0346, 0x0356, 0x0467, 0x0356, 0x0467, 0x0467,
			0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
			0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
			0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
			0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff
		};

		SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(pixels, 16, 16, 16, 32, 0x0f00, 0x00f0, 0x000f, 0xf000);
		SDL_SetWindowIcon(m_sdlWindow, surface);
		SDL_FreeSurface(surface);

		//Set up our OpenGL context
		SDL_GLContext glContext = SDL_GL_CreateContext(m_sdlWindow);
		if (glContext == nullptr) {
			fatalError("SDL_GL context could not be created!");
		}

		//Set up glew (optional but recommended)
		GLenum error = glewInit();
		if (error != GLEW_OK) {
			fatalError("Could not initialize glew!");
		}

		//Clear to "Windows Blue"
		glClearColor(0.5f, 1.0f, 0.5f, 1.0f);

		//vsync
		//SDL_GL_SetSwapInterval(1);

		//Multisampling (4x)
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
		glEnable(GL_MULTISAMPLE);

		//Enable alpha transparency
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		FillDisplaysProps();

		return 0;
	}

	void Window::setMouseCoords(signed int eventMouseX, signed int eventMouseY) 	{
		
		m_mouseX = eventMouseX;
		m_mouseY = eventMouseY;

	}

	//Swap Buffers
	void Window::SwapBuffers() {
		//Swap our buffer and draw everything to the screen!
		SDL_GL_SwapWindow(m_sdlWindow);
	}

	int Window::GetDisplayProperty(const DisplayProps& DisplayProperty) {

		switch (DisplayProperty) {
		case DisplayProps::WIDTH:
			return m_properties.width;
			break;
		case DisplayProps::HEIGHT:
			return m_properties.height;
			break;
		case DisplayProps::REFRESHRATE:
			return m_properties.refresh_rate;
			break;
		}
	}

	void Window::FillDisplaysProps() {
		
		SDL_DisplayMode Mode;
		int DisplayIndex = SDL_GetWindowDisplayIndex(m_sdlWindow);
		// If we can't find the refresh rate, we'll return this:
		int DefaultRefreshRate = 60;
		if (SDL_GetDesktopDisplayMode(DisplayIndex, &Mode) != 0) {
			m_properties.refresh_rate = DefaultRefreshRate;
		}
		if (Mode.refresh_rate == 0) {
			m_properties.refresh_rate = DefaultRefreshRate;
		}
		else {
			m_properties.refresh_rate = Mode.refresh_rate;
		}
		m_properties.width = Mode.w;
		m_properties.height = Mode.h;
	}
}