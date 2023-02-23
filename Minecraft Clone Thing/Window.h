#pragma once
#include<glad/glad.h>
#include<glfw3.h>
#define STARTUP_MONITOR_2 true

struct Window {
	public:
		static const int windowWidth = 1280;
		static const int windowHeight = 720;
		static const char* windowTitle;
		
		static void fullScreen(GLFWwindow* window);
		static bool isFullScreen(GLFWwindow* window);
		static void setWindowScreen(GLFWwindow* window);
	private:
		 static int screenPosX, screenPosY, screenWidth, screenHeight;
};

