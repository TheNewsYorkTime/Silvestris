#include "Monitor.h"

std::vector <Monitor> monitors;

void  monitorsSetup() {
	int count;
	GLFWmonitor** nativeMonitors = glfwGetMonitors(&count);
	for ( int i = 0; i < count; i++ ) {
		int xpos, ypos, width, height;
		glfwGetMonitorWorkarea(nativeMonitors[i], &xpos, &ypos, &width, &height);
		monitors.push_back({ { xpos, ypos }, { width, height }, nativeMonitors[i], i, true });
	}
}

void onMonitorsChange(GLFWmonitor* monitor, int event) {
	//first use of lambdas
	auto place = std::find_if(monitors.begin(), monitors.end(), [&monitor](Monitor currMonitor) {return currMonitor.nativeMonitor == monitor;});
	if ( event == GLFW_CONNECTED ) {
		if(place != monitors.end()) (*place).connected = true;

		else {
			int xpos, ypos, width, height;
			glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height);
			monitors.push_back({ { xpos, ypos }, { width, height }, monitor, (int) std::distance(monitors.begin(), monitors.end()), true });
		}
	}

	else if ( event == GLFW_DISCONNECTED ) {
		if ( place != monitors.end() ) (*place).connected = false;
	}
	else {
		printf("Warning: Unknown Monitor Event: %d", event);
	}
}