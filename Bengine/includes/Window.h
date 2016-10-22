#ifndef WINDOW_H
#define WINDOW_H

#include <SDL\include\SDL.h>
#include <GL\glew.h>
#include "ErrorSuite.h"
#include <Windows.h>

#include <string>

namespace Engine {
	enum WindowFlags {
		INVISIBLE = 0x1,
		FULLSCREEN = 0x2,
		BORDERLESS = 0x4
	};

	enum CursorOptions {
		NOCURSOR = 0x1,
		CUSTOMCURSOR = 0x2
	};

	enum DisplayProps {
		WIDTH = 0,
		HEIGHT = 1,
		REFRESHRATE = 2
	};

	class Window {

	public:
		Window();
		~Window();

		int CreateNewWindow(const std::string& windowName, unsigned int windowflags, const std::string& windowIcon);

		void setMouseCoords(signed int eventMouseX, signed int eventMouseY);
		void SwapBuffers();

		float getScreenWidth() const { return m_screenWidth; };
		float getScreenHeight() const { return m_screenHeight; };

		unsigned int getmouseX() { return m_mouseX; };
		unsigned int getMouseY() { return m_mouseY; };

		int getWindowWidth() { return SDL_GetWindowSurface(m_sdlWindow)->w; };
		int getWindowHeight() { return SDL_GetWindowSurface(m_sdlWindow)->h; };

		int GetDisplayProperty(const DisplayProps& DisplayProperty);

	private:

		void FillDisplaysProps();

		SDL_Window* m_sdlWindow;

		const float m_screenWidth = GetSystemMetrics(SM_CXSCREEN) / 1.5;
		const float m_screenHeight = GetSystemMetrics(SM_CYSCREEN) / 1.5;

		signed int m_mouseX, m_mouseY;

		struct DisplayProperties {
		public:
			int width;
			int height;
			int refresh_rate;
		} m_properties;
	};
}
#endif // !WINDOW_H