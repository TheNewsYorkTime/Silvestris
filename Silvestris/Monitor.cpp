#include "Monitor.h"

std::vector <Monitor> monitors;

void monitorsSetup() {
	int count;
	GLFWmonitor** nativeMonitors = glfwGetMonitors(&count);
	for ( int i = 0; i < count; i++ ) {
		int xpos, ypos, width, height;
		glfwGetMonitorWorkarea(nativeMonitors [i], &xpos, &ypos, &width, &height);
		monitors.push_back({ xpos, ypos, width, height, nativeMonitors [i] });
	}
}

void onMonitorsChange(GLFWmonitor* monitor, int event) {
	if ( event == GLFW_CONNECTED ) {
		int xpos, ypos, width, height;
		glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height);
		monitors.push_back({ xpos, ypos, width, height, monitor });
		return;
	}
	// may work
	else if ( event == GLFW_DISCONNECTED ) {
		auto place = std::find_if(monitors.begin(),monitors.end(),[&monitor](Monitor currMonitor) {return currMonitor.nativeMonitor == monitor;});
		if (place != monitors.end()) monitors.erase(place);
	}
	else {
		printf("Warning: Unknown Monitor Event: %d", event);
	}
}