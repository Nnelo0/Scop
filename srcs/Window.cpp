#include "all.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int heigth)
{
	(void)window;
	glViewport(0, 0, width, heigth);
}

void processInput(GLFWwindow *window, Obj &obj, WindowInfo &windowInfo)
{
	//close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//move object
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) obj.position[0] -= 0.2;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) obj.position[0] += 0.2;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS) obj.position[1] += 0.2;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS) obj.position[1] -= 0.2;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) obj.position[2] += 0.2;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) obj.position[2] -= 0.2;

	//reset Object
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		obj.position[0] = 0.0f;
		obj.position[1] = 0.0f;
		obj.position[2] = 0.0f;
		obj.rotation[0] = 0.0f;
		obj.rotation[1] = 0.0f;
		obj.rotation[2] = 0.0f;
	}

	// stop rotating object
	bool SpacePressedNow = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
	if (SpacePressedNow && !windowInfo.spacePressedLastFrame) {
		obj.toggleRotation = !obj.toggleRotation;
	}
	windowInfo.spacePressedLastFrame = SpacePressedNow;

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
	
	windowInfo.spacePressedLastFrame = false;
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
	// glfwSwapInterval(0); this is fun...

	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		throw runtime_error ("failed to initialize Glew\n");
	}
	glViewport(0, 0, 1920, 1080);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glEnable(GL_DEPTH_TEST);

	return window;
}
