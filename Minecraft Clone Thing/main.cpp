#include<glad/glad.h>
#include<glfw3.h>
#include<glm/vec3.hpp>
#include<glm/common.hpp>
#include<glm/matrix.hpp>
#include<iostream>
#include "Window.h"
#include "Input.h"

using namespace std;

void handle_glfw_error(int error, const char* description) {
	fprintf(stderr, "GLFW had an error: %s\n", description);
};
void onMouseScroll(GLFWwindow* window, double xoffset, double yoffset) {
	printf("Scrolllll! Weee!\n");
}
void onMouseMove(GLFWwindow* window, double xpos, double ypos) {
	printf("Mouse is moving over the window at: %f, %f\n", xpos, ypos);
};
int main() {
	if (!glfwInit()) {
		printf("Failed to initialize GLFW, exiting.......\n");
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(
		Window::windowWidth,
		Window::windowHeight,
		Window::windowTitle,
		nullptr,
		nullptr
	);
	if (window == nullptr) {
		printf("No window was created, ending...\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	Window::setWindowScreen(window);
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("GLAD failed to initialize, exiting...\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetErrorCallback(handle_glfw_error);
	glfwSetKeyCallback(window, Input::onKey);
	glfwSetCursorPosCallback(window, onMouseMove);
	glfwSetScrollCallback(window, onMouseScroll);
	glViewport(0, 0, Window::windowWidth, Window::windowHeight);
	while (!glfwWindowShouldClose(window)) {
		glClearColor(250.0f / 255.0f, 119.0f /255.0f, 10.0f /255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();
	return 0;
}
