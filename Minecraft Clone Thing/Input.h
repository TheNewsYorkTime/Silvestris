#include "core.h"

class Input {
	public:
		static void onKey(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void onMouseButton(GLFWwindow* window, int button, int action, int mods);
		static void onMouseMove(GLFWwindow* window, double xpos, double ypos);
		static void onMouseScroll(GLFWwindow* window, double xoffset, double yoffset);
		static bool checkKeyDown(int key, bool held);
		static bool checkMouseButtonDown(int button);
		static void inputs(Window* window);

		

	private:
		static int keysPressed[GLFW_KEY_LAST];
		static bool mouseButtonData[GLFW_MOUSE_BUTTON_LAST];
		static double mouseX;
		static double mouseY;
		static float mouseScrollX;
		static float mouseScrollY;
};
