#pragma once
#include "core.h"
#define MAX_MONITORS 10

typedef struct Monitor {
	int xpos;
	int ypos;
	int xsize;
	int ysize;
	GLFWmonitor* nativeMonitor;
};

void monitorsSetup();
void onMonitorsChange(GLFWmonitor* monitor, int event);

extern Monitor monitors[MAX_MONITORS];