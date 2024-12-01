#include "RenderManager.h"

uint32_t RenderManager::myVAOId = NULL;
uint32_t RenderManager::myVBOId = NULL;
int RenderManager::worldX, RenderManager::worldY = 0;

void RenderManager::uploadVerticesAndStuff() {
	glm::vec3 verts[4] = {
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(-0.5f, 0.5f, 0.0f),
		glm::vec3(0.5f ,-0.5f, 0.0f),
		glm::vec3(0.5f, 0.5f, 0.0f) };

	Object square = Object(verts, glm::vec4(0.5f, 0.3f, 0.3f, 1.0f), 4);

	glGenVertexArrays(1, &myVAOId);
	glBindVertexArray(myVAOId);


	glGenBuffers(1, &myVBOId);
	glBindBuffer(GL_ARRAY_BUFFER, myVBOId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square.vertices), &square.vertices.at(0), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
}
void RenderManager::drawStuff(Window* window) {
	glClearColor(100.0f / 255.0f, 237.0f / 255.0f, 223.0f / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(myVAOId);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glfwSwapBuffers(window->nativeWindow);
}
void RenderManager::framebufferCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	Window* renderWindow = Window::getWindow(window);
	RenderManager::drawStuff(renderWindow);
}
void RenderManager::setWorldSpace(int x, int y, Window* window) {
	worldX = x;
	RenderManager::worldY = y;
	glfwSetWindowAspectRatio(window->nativeWindow, x, y);

}