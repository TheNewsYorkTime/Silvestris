#pragma once
#include "core.h"
#include "Window.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;
};
class RenderManager {
	public: 
		static uint32_t myVAOId;
		static uint32_t myVBOId;
		static int worldX;
		static int worldY;
		static void uploadVerticesAndStuff();
		static void drawStuff(Window* window);
		static void framebufferCallback(GLFWwindow* window, int width, int height);
		static void setWorldSpace(int x, int y, Window* window);
};
