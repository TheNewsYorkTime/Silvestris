#include "Window.h"
#include "Input.h"



// TODO: Refactor with Window User Pointer
std::vector <Window*> Window::activeWindows;

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

void monitorAfterMove(GLFWwindow* window, int posX, int posY) {
	Window* movedWindow = Window::getWindow(window);
	movedWindow->getWindowMonitor();
	glfwSetWindowSizeLimits(movedWindow->nativeWindow, NULL, NULL, movedWindow->windowMonitor->xsize, movedWindow->windowMonitor->ysize);
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
	GLFWwindowposfun pos = glfwSetWindowPosCallback(window, monitorAfterMove);
	return 0;
}

Window* Window::createWindow(const char* title, int width, int height)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
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
	Window::activeWindows.push_back(createdWindow);
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
	for (auto window : Window::activeWindows) {
		if (window->nativeWindow == windowIn) {
			return retWindow = window;
		}
	}
	return nullptr;
}

void Window::removeWindow(GLFWwindow* windowIn) {
	auto windowWindowToFind = Window::getWindow(windowIn);
	auto windowIndex = std::find(Window::activeWindows.begin(), Window::activeWindows.end(), windowWindowToFind);
	Window::activeWindows.erase(windowIndex);
}
void Window::fullScreen() {
	if (this->isFullScreen()) {
		glfwSetWindowMonitor(this->nativeWindow, nullptr, this->windowPosX, this->windowPosY, windowHeight, windowWidth, GLFW_DONT_CARE);
	}
	else {
		glfwGetWindowPos(this->nativeWindow, &this->windowPosX, &this->windowPosY);
		this->getWindowMonitor();

		printf("Setting to Monitor: %s\n", glfwGetMonitorName(this->windowMonitor->nativeMonitor));
		int xpos, ypos, width, height;
		glfwGetMonitorWorkarea(this->windowMonitor->nativeMonitor, &xpos, &ypos, &width, &height);
		printf("Monitor: %s, Inner Bound (%d, %d), Outer Bound (%d, %d), actual position: (%d, %d)\n", glfwGetMonitorName(this->windowMonitor->nativeMonitor), xpos, ypos, xpos + width, ypos + height, this->windowPosX, this->windowPosY);
		glfwSetWindowMonitor(this->nativeWindow, this->windowMonitor->nativeMonitor, xpos, ypos, width, height, GLFW_DONT_CARE);
	}
}

void Window::getWindowMonitor() {
	glfwGetWindowPos(this->nativeWindow, &this->windowPosX, &this->windowPosY);
	for (auto monitor : monitors) {
		if ( this->windowPosX >=  monitor.xpos && this->windowPosX <= monitor.xpos + monitor.xsize  - (this->windowWidth / 3)
			&& this->windowPosY >= monitor.ypos && this->windowPosY <= monitor.ysize + monitor.ypos - (this->windowWidth / 3) ) {

				this->windowMonitor = &monitor;
				return;
			}
	}
	return;
}

bool Window::isFullScreen() {
	return glfwGetWindowMonitor(this->nativeWindow) != nullptr;
}
void Window::setWindowScreen(int screen) {

	if (monitors[screen - 1].nativeMonitor == 0) {
		fprintf(stderr, "Can't set window to screen %d. No such screen\n", screen);
		return;
	}
	this->windowMonitor = &monitors[screen - 1];
	glfwSetWindowPos(this->nativeWindow, monitors[screen - 1].xpos + monitors[screen - 1].xsize / 2 - windowWidth / 2, monitors[screen - 1].ypos + monitors[screen - 1].ysize / 2 - windowHeight / 2);
}