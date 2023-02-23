#include<glad/glad.h>
#include<glfw3.h>
#include "Window.h"
#include "Input.h"

void Input::onKey(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
		Window::fullScreen(window);
	}

};