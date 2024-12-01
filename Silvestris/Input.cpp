#include "Window.h"
#include "Input.h"

int Input::keysPressed[GLFW_KEY_LAST] = {};
bool Input::mouseButtonData[GLFW_MOUSE_BUTTON_LAST] = {};
ash::vec2 <double> Input::mouse = { 0.0, 0.0 };
ash::vec2 <float> Input::mouseScroll = { 0.0f, 0.0f };

void Input::onKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key >= 0 && key < GLFW_KEY_LAST)
	{
		keysPressed[key] = action;
	}
}
void Input::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST)
	{
		mouseButtonData[button] = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
	}
}
;

void Input::onMouseScroll(GLFWwindow* window, double xoffset, double yoffset) {
	mouseScroll.x = (float)xoffset;
	mouseScroll.y = (float)xoffset;
	printf("Scrolllll! Weee!\n");
}
void Input::onMouseMove(GLFWwindow* window, double xpos, double ypos) {
	mouse.x = xpos;
	mouse.y = ypos;
	printf("Mouse is moving over the window at: %f, %f\n", xpos, ypos);
};

bool Input::checkKeyDown(int key, bool held = false) {
	if (key >= 0 && key < GLFW_KEY_LAST)
	{
		if (held)
		{
			return (keysPressed[key] == GLFW_REPEAT);
		}
		return (keysPressed[key] == GLFW_PRESS);
	}

	return false;
}

bool Input::checkMouseButtonDown(int button)
{
	if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST)
	{
		return mouseButtonData[button];
	}

	return false;
}

void Input::inputs(Window* window)
{
	if (Input::checkKeyDown(GLFW_KEY_F11) || (Input::checkKeyDown(GLFW_KEY_ESCAPE) && window->isFullscreen())) {
		window->fullscreen();
	}
	keysPressed[GLFW_KEY_F11] = {};
}
