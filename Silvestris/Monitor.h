#pragma once
#include "core.h"

struct Monitor {
	ash::vec2 <int> pos;
	ash::vec2 <int> size;
	GLFWmonitor* nativeMonitor;
	int id;
	bool connected;
};

void monitorsSetup();
void onMonitorsChange(GLFWmonitor* monitor, int event);

extern std::vector <Monitor> monitors;