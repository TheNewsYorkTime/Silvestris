#pragma once
#ifndef SILVESTRIS
#define SILVESTRIS
#include "core.h"
#include <iterator>
#include "./utils/arrays.h"
#define STARTUP_MONITOR 2
#define STARTUP_FULLSCREEN false
#define MAX_WINDOWS 5

class Window {
	public:
		GLFWwindow* nativeWindow;
		int windowWidth;
		int windowHeight;
		const char* windowTitle;
		int windowMonitor;
		
		static Window* createWindow(const char* title, int width, int height);
		static Window* getWindow(GLFWwindow* windowIn);
		static int  getWindow(Window* windowIn);
		static void addWindow(Window* window);
		static void removeWindow(GLFWwindow* windowIn);
		void fullScreen();
		bool isFullScreen(Window* window);
		void setWindowScreen(int screen);
		void getWindowMonitor();
	private:
		int windowPosX, windowPosY;
		static Window* activeWindows[MAX_WINDOWS];
};
#endif