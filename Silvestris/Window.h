#pragma once
#ifndef SILVESTRIS
#define SILVESTRIS
#include "core.h"
#include <iterator>
#include "./utils/arrays.h"
#define STARTUP_MONITOR 0
#define STARTUP_FULLSCREEN false
#include "Monitor.h"

class Window {

	public:

		Window(const char* title, int width, int height);

		GLFWwindow* nativeWindow;
		int windowWidth;
		int windowHeight;
		const char* windowTitle;
		Monitor* windowMonitor;

		static Window* getWindow(GLFWwindow* windowIn);
		static void removeWindow(GLFWwindow* windowIn);
		static void onWindowSizeChange(GLFWwindow* window, int width, int height);
		static void monitorAfterMove(GLFWwindow* window, int posX, int posY);
		static int applyCallbacks(GLFWwindow* window);
		void fullscreen();
		bool isFullscreen() const;
		void setWindowMonitor(int id);
		void getWindowMonitor();

	private:
		ash::vec2 <int> windowPos;
		static std::vector <Window*> activeWindows;
};
#endif