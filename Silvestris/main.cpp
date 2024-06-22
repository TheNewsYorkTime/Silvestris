#include "core.h"
#include "main.h"
#include "RenderManager.h"
#include "Shader.h"


using namespace std;

Shader shader;

int main() {

	if (!glfwInit()) {
		printf("Failed to initialize GLFW, exiting.......\n");
		exit(EXIT_FAILURE);
	}

	monitorsSetup();

	Window* mainWindow = Window::createWindow("Silvestris", 1280, 720);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("GLAD failed to initialize, exiting...\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	shader.compile();
	
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(mainWindow->nativeWindow, RenderManager::framebufferCallback);
	RenderManager::uploadVerticesAndStuff();
	shader.bind();

	//main loop
	while (!glfwWindowShouldClose(mainWindow->nativeWindow)) {
		
		glViewport(0, 0, mainWindow->windowWidth, mainWindow->windowHeight);
		
		
		RenderManager::drawStuff(mainWindow);


		glfwPollEvents();

		Input::inputs(mainWindow);
	}
	
	glfwTerminate();
	return 0;
}
