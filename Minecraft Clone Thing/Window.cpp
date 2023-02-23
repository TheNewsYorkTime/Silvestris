#include<glad/glad.h>
#include<glfw3.h>
#include<iostream>
#include "Window.h"
const char* Window::windowTitle = "Minecraft Clone";
int Window::screenPosX = NULL, Window::screenPosY = NULL, Window::screenWidth = 0, Window::screenHeight = 0;
void Window::fullScreen(GLFWwindow* window) {
	if (isFullScreen(window)) {
		glfwGetWindowPos(window, &screenPosX, &screenPosY);
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		int xpos, ypos, width, height;
		glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height);
		glfwSetWindowMonitor(window, monitor, xpos, ypos, width, height, GLFW_DONT_CARE);
	}
	else {
		glfwSetWindowMonitor(window, nullptr, screenPosX, screenPosY, 1280, 720, GLFW_DONT_CARE);
	}
}
bool Window::isFullScreen(GLFWwindow* window) {
	return glfwGetWindowMonitor(window) == nullptr;
}
void Window::setWindowScreen(GLFWwindow* window) {
	int count;
	GLFWmonitor** monitors = glfwGetMonitors(&count);
	GLFWmonitor* monitor = monitors[1];
	if (STARTUP_MONITOR_2) {
		glfwGetMonitorPos(monitor, &screenPosX, &screenPosY);
		glfwGetMonitorWorkarea(monitor, &screenPosX, &screenPosY, &screenWidth, &screenHeight);
		glfwSetWindowPos(window, screenPosX + screenWidth / 5, screenPosY + screenHeight / 5);
	}
}