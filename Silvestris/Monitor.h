#pragma once
#include "core.h"

struct Monitor {
	int xpos;
	int ypos;
	int xsize;
	int ysize;
	GLFWmonitor* nativeMonitor;
};

void monitorsSetup();
void onMonitorsChange(GLFWmonitor* monitor, int event);

extern std::vector <Monitor> monitors;