#include "Monitor.h"
#include "./utils/arrays.h"

Monitor monitors[MAX_MONITORS];

void monitorsSetup() {
	int count;
	GLFWmonitor** nativeMonitors = glfwGetMonitors(&count);
	for (int i = 0; i < count; i++) {
		int xpos, ypos, width, height;
		glfwGetMonitorWorkarea(nativeMonitors[i], &xpos, &ypos, &width, &height);
		monitors[i] = { xpos, ypos, width, height, nativeMonitors[i] };
	}
}

void onMonitorsChange(GLFWmonitor* monitor, int event) {
	if (event == GLFW_CONNECTED) {
		for (int i = 0; i < MAX_MONITORS; i++) {
			if (monitors[i].nativeMonitor == NULL) {
				int xpos, ypos, width, height;
				glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height);
				monitors[i] = { xpos, ypos, width, height, monitor };
				return;
			}
		}
	}
	//may work
	else if (event == GLFW_DISCONNECTED) {
		int index = 0;
		for (int i = 0; i < MAX_MONITORS; i++) {
			if (monitors[i].nativeMonitor == monitor) {
				index = i;
				break;
			}
		}
		popItem(&monitors, sizeof(Monitor), index, sizeof(monitors));
	}
	else {
		printf("Warning: Unknown Monitor Event: %d", event);
	}
}