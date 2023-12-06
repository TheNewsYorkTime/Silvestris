#include "Window.h"
#include "Input.h"
#include "Monitor.h"

Window* Window::activeWindows[MAX_WINDOWS] = {nullptr};

void handle_glfw_error(int error, const char* description) {
	fprintf(stderr, "GLFW had an error: %s\n", description);
};

void onWindowClose(GLFWwindow* window) {
	Window::removeWindow(window);

}

void onWindowSizeChange(GLFWwindow* window, int width, int height) {
	Window* actingWindow = Window::getWindow(window);
	actingWindow->windowWidth = width;
	actingWindow->windowHeight = height;
}

int applyCallbacks(GLFWwindow* window) {
	GLFWerrorfun error = glfwSetErrorCallback(handle_glfw_error);
	GLFWmonitorfun monitor = glfwSetMonitorCallback(onMonitorsChange);
	GLFWwindowsizefun size = glfwSetWindowSizeCallback(window, onWindowSizeChange);
	GLFWwindowclosefun close = glfwSetWindowCloseCallback(window, onWindowClose);
	GLFWkeyfun key  = glfwSetKeyCallback(window, Input::onKey);
	GLFWcursorposfun cursor = glfwSetCursorPosCallback(window, Input::onMouseMove);
	GLFWscrollfun scroll = glfwSetScrollCallback(window, Input::onMouseScroll);
	GLFWmousebuttonfun mouse = glfwSetMouseButtonCallback(window, Input::onMouseButton);
	return 0;
}

Window* Window::createWindow(const char* title, int width, int height)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window* createdWindow = new Window();

	createdWindow->nativeWindow = glfwCreateWindow(
		width,
		height,
		title,
		nullptr,
		nullptr
	);
	if (createdWindow->nativeWindow == nullptr) {
		printf("No window was created, ending...\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	Window::addWindow(createdWindow);
	applyCallbacks(createdWindow->nativeWindow) == 0 ? printf("Callbacks attatched\n") : fprintf(stderr, "Callbacks not attached\n");
	createdWindow->windowWidth = width;
	createdWindow->windowHeight = height;

	createdWindow->setWindowScreen(STARTUP_MONITOR);

	if (STARTUP_FULLSCREEN)
	{
		createdWindow->fullScreen();
	}
	glfwMakeContextCurrent(createdWindow->nativeWindow);
	
	return createdWindow;
}
Window* Window::getWindow(GLFWwindow* windowIn) {
	Window* retWindow = nullptr;
	for (int i = 0; i < MAX_WINDOWS; i++) {
		if (Window::activeWindows[i]->nativeWindow == windowIn) {
			return retWindow = Window::activeWindows[i];
		}
	}
	return nullptr;
}
int Window::getWindow(Window* windowIn) {
	int index;
	for (int i = 0; i < MAX_WINDOWS; i++) {
		if (Window::activeWindows[i] == windowIn) {
			index = i;
		}
	}
	return index;
}
void Window::addWindow(Window* window) {
	for (int i = 0; i < MAX_WINDOWS; i++) {
		if (Window::activeWindows[i] == nullptr) {
			Window::activeWindows[i] = window;
			return;
		}
	}
}
void Window::removeWindow(GLFWwindow* windowIn) {
	int windowIndex = getWindow(getWindow(windowIn));
	popItem(Window::activeWindows, sizeof(Window *), windowIndex, sizeof(Window::activeWindows));
}
void Window::fullScreen() {
	if (isFullScreen(this)) {
		glfwSetWindowMonitor(this->nativeWindow, nullptr, this->windowPosX, this->windowPosY, 1280, 720, GLFW_DONT_CARE);
	}
	else {
		glfwGetWindowPos(this->nativeWindow, &this->windowPosX, &this->windowPosY);
		this->getWindowMonitor();
		printf("Setting to Monitor: %d\n", this->windowMonitor);
		int xpos, ypos, width, height;
		glfwGetMonitorWorkarea(monitors[this->windowMonitor].nativeMonitor, &xpos, &ypos, &width, &height);
		glfwSetWindowMonitor(this->nativeWindow, monitors[this->windowMonitor].nativeMonitor, xpos, ypos, width, height, GLFW_DONT_CARE);
	}
}

void Window::getWindowMonitor() {
	glfwGetWindowPos(this->nativeWindow, &this->windowPosX, &this->windowPosY);
	for (int i = 0; i < 10; i++) {
		if (this->windowPosX >=  monitors[i].xpos && this->windowPosX <= monitors[i].xsize  - (this->windowWidth / 2) 
			&& this->windowPosY >= monitors[i].ypos && this->windowPosY <= monitors[i].ysize) {

				this->windowMonitor = i;
				return;
			}
	}
	return;
}

bool Window::isFullScreen(Window* window) {
	return glfwGetWindowMonitor(window->nativeWindow) != nullptr;
}
void Window::setWindowScreen(int screen) {
	if (monitors[screen - 1].nativeMonitor == 0) {
		fprintf(stderr, "Can't set window to screen %d. No such screen\n", screen);
		return;
	}
	this->windowMonitor = screen - 1;
	glfwSetWindowPos(this->nativeWindow, monitors[screen - 1].xpos + monitors[screen - 1].xsize / 2 - windowWidth / 2, monitors[screen - 1].ypos + monitors[screen - 1].ysize / 2 - windowHeight / 2);
}