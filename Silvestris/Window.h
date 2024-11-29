#pragma once
#ifndef SILVESTRIS
#define SILVESTRIS
#include "core.h"
#include <iterator>
#include "./utils/arrays.h"
#define STARTUP_MONITOR 2
#define STARTUP_FULLSCREEN false
#include "Monitor.h"

class Window {
	public:
		GLFWwindow* nativeWindow;
		int windowWidth;
		int windowHeight;
		const char* windowTitle;
		Monitor* windowMonitor;

		static Window* createWindow(const char* title, int width, int height);
		static Window* getWindow(GLFWwindow* windowIn);
		static void removeWindow(GLFWwindow* windowIn);
		void fullScreen();
		bool isFullScreen();
		void setWindowScreen(int screen);
		void getWindowMonitor();
	private:
		int windowPosX, windowPosY;
		static std::vector <Window*> activeWindows;
};
#endif