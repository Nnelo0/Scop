#include "all.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int heigth)
{
	(void)window;
	glViewport(0, 0, width, heigth);
}

void processInput(GLFWwindow *window, Obj &obj, Camera &cam, WindowInfo &windowInfo)
{
	//close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	obj.objectInput(window, windowInfo);

	cam.camInput(window);

	// Change speed
	bool ShiftPressedNow = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
	if (ShiftPressedNow) {
		obj.speed = 0.6f;
		cam.speed = 0.4f;
	}
	else {
		obj.speed = 0.2f;
		cam.speed = 0.2f;
	}

	// Toggle Texture
	bool TPressedNow = glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS;
	if (TPressedNow && !windowInfo.TPressedLastFrame) {
		obj.toggleTexture = !obj.toggleTexture;
	}
	windowInfo.TPressedLastFrame = TPressedNow;

	// Toggle Debug Window
	bool TabPressedNow = glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS;
	if (TabPressedNow && !windowInfo.TabPressedLastFrame) {
		windowInfo.showDebugWindow = !windowInfo.showDebugWindow;
	}
	windowInfo.TabPressedLastFrame = TabPressedNow;
}

void initWindowInfo(WindowInfo &windowInfo)
{
	windowInfo.BackgroundColors[0] = 0.4f;
	windowInfo.BackgroundColors[1] = 0.3f;
	windowInfo.BackgroundColors[2] = 0.69f;
	
	windowInfo.pPressedLastFrame = false;
	windowInfo.TPressedLastFrame = false;
	windowInfo.TabPressedLastFrame = false;

	windowInfo.showDebugWindow = false;
}

GLFWwindow *initWindow(string nameWindow)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(1920, 1080, (string("Scop - ") + nameWindow).c_str(), NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		throw runtime_error("failed to create window\n");
	}
	glfwMakeContextCurrent(window);
	// glfwSwapInterval(0); //this is fun...

	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		throw runtime_error ("failed to initialize Glew\n");
	}
	glViewport(0, 0, 1920, 1080);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glEnable(GL_DEPTH_TEST);

	return window;
}
