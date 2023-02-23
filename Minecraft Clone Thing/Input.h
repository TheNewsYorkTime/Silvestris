#pragma once
#include<glad/glad.h>
#include<glfw3.h>

class Input {
	public:
		static void onKey(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void onMouseMove(GLFWwindow* window, double xpos, double ypos);
		static void onMouseScroll(GLFWwindow* window, double xoffset, double yoffset);
};

