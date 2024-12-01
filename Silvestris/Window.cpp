#include "Window.h"
#include "Input.h"



// TODO: Refactor with Window User Pointer
std::vector <Window*> Window::activeWindows;

void handle_glfw_error(int error, const char* description) {
	fprintf(stderr, "GLFW had an error: %s\n", description);
};

Window::Window(const char* title, int width, int height)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->nativeWindow = glfwCreateWindow(
		width,
		height,
		title,
		nullptr,
		nullptr
	);
	if (this->nativeWindow == nullptr) {
		printf("No window was created, ending...\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	Window::activeWindows.push_back(this);

	applyCallbacks(this->nativeWindow) == 0 ? printf("Callbacks attached\n") : fprintf(stderr, "Callbacks not attached\n");



	this->windowWidth = width;
	this->windowHeight = height;

	setWindowMonitor(STARTUP_MONITOR);


	if (STARTUP_FULLSCREEN)
	{
		this->fullscreen();
	}
	glfwMakeContextCurrent(this->nativeWindow);
}

Window* Window::getWindow(GLFWwindow* windowIn) {

	return *std::find_if(Window::activeWindows.begin(),Window::activeWindows.end(),
		[windowIn](Window* window) {
		return windowIn == window->nativeWindow;
	});
}

void Window::removeWindow(GLFWwindow* windowIn) {
	auto windowWindowToFind = Window::getWindow(windowIn);
	auto windowIndex = std::find(Window::activeWindows.begin(), Window::activeWindows.end(), windowWindowToFind);
	Window::activeWindows.erase(windowIndex);
}

void Window::onWindowSizeChange(GLFWwindow* window, int width, int height) {
	Window* actingWindow = Window::getWindow(window);
	actingWindow->windowWidth = width;
	actingWindow->windowHeight = height;
}

void Window::monitorAfterMove(GLFWwindow* window,int posX,int posY) {
	Window* movedWindow = Window::getWindow(window);
	movedWindow->getWindowMonitor();
}

int Window::applyCallbacks(GLFWwindow* window) {
	GLFWerrorfun error = glfwSetErrorCallback(handle_glfw_error);
	GLFWmonitorfun monitor = glfwSetMonitorCallback(onMonitorsChange);
	GLFWwindowsizefun size = glfwSetWindowSizeCallback(window,Window::onWindowSizeChange);
	GLFWwindowclosefun close = glfwSetWindowCloseCallback(window,Window::removeWindow);
	GLFWkeyfun key  = glfwSetKeyCallback(window,Input::onKey);
	GLFWcursorposfun cursor = glfwSetCursorPosCallback(window,Input::onMouseMove);
	GLFWscrollfun scroll = glfwSetScrollCallback(window,Input::onMouseScroll);
	GLFWmousebuttonfun mouse = glfwSetMouseButtonCallback(window,Input::onMouseButton);
	GLFWwindowposfun pos = glfwSetWindowPosCallback(window,Window::monitorAfterMove);
	return 0;
}

void Window::fullscreen() {
	if (this->isFullscreen()) {
		glfwSetWindowMonitor(this->nativeWindow, nullptr, this->windowPos.x, this->windowPos.y, windowHeight, windowWidth, GLFW_DONT_CARE);
	}
	else {
		glfwGetWindowPos(this->nativeWindow, &this->windowPos.x, &this->windowPos.y);
		this->getWindowMonitor();

		printf("Setting to Monitor: %s\n", glfwGetMonitorName(this->windowMonitor->nativeMonitor));
		int xpos, ypos, width, height;
		glfwGetMonitorWorkarea(this->windowMonitor->nativeMonitor, &xpos, &ypos, &width, &height);
		printf("Monitor: %s, Inner Bound (%d, %d), Outer Bound (%d, %d), actual position: (%d, %d)\n", glfwGetMonitorName(this->windowMonitor->nativeMonitor), xpos, ypos, xpos + width, ypos + height, this->windowPos.x, this->windowPos.y);
		glfwSetWindowMonitor(this->nativeWindow, this->windowMonitor->nativeMonitor, xpos, ypos, width, height, GLFW_DONT_CARE);
	}
}

bool Window::isFullscreen() const {
	return glfwGetWindowMonitor(this->nativeWindow) != nullptr;
}

void Window::setWindowMonitor(int id) {
	auto monitor = find_if(monitors.begin(), monitors.end(), [&id](Monitor monitor) { return monitor.id == id; });

	if( monitor == monitors.end() ) {
		fprintf(stderr, "Can't set window to monitor id: %d, name %s. No such monitor\n", id, glfwGetMonitorName(monitor->nativeMonitor));
		return;
	}
	this->windowMonitor = &*monitor;
	glfwSetWindowPos(this->nativeWindow, monitor->pos.x + monitor->size.x / 2 - this->windowWidth / 2, monitor->pos.y + monitor->size.y / 2 - windowHeight / 2);
}

void Window::getWindowMonitor() {
	glfwGetWindowPos(this->nativeWindow, &this->windowPos.x, &this->windowPos.y);
	for(auto &monitor : monitors) {
		if(this->windowPos.x >=  monitor.pos.x
			&& this->windowPos.x <= monitor.pos.x + monitor.size.x  - (this->windowWidth / 3)
			&& this->windowPos.y >= monitor.pos.y
			&& this->windowPos.y <= monitor.size.y + monitor.pos.y - (this->windowWidth / 3)) {

			this->windowMonitor = &monitor;
			glfwSetWindowSizeLimits(this->nativeWindow, NULL, NULL, this->windowMonitor->size.x, this->windowMonitor->size.y);
			return;
		}
	}
	return;
}