#include "all.hpp"

int main(int argc, char **argv)
{
	try
	{
		Obj obj(argv[1]);
		obj.generateUVs(obj.vertices);

		if (!glfwInit()) {
			std::cerr << "failed to init\n";
			return -1;
		}

		WindowInfo windowInfo;
		initWindowInfo(windowInfo);
		GLFWwindow *window = initWindow(obj.name);

		ImGuiIO& io = initImGui(window);

		unsigned int VAO = initBuffers(obj);
		glBindVertexArray(0);

		Shaders shader("shaders/vertex.vert", "shaders/fragment.frag");
		GLint modelLoc = matrixParameters(shader);

		GLuint texture;
		if (argc == 3) {
			texture = loadTexture(argv[2]);
			obj.hasTexture = true;
			glUniform1i(glGetUniformLocation(shader.shaderProgram, "uUseTexture"), 0);
		}

		// cout	<< "┌----------------------------------------┐"
		// 		<< "|                Commands                |"
		// 		<< "|   Movements :                          |"
		// 		<< "|  	  - ↑                                |"
		// 		<< "|  	  - ↓                                |"
		// 		<< "|  	  - →                                |"
		// 		<< "|  	  - ←                                |"
		// 		<< "|  	  - PgUp                             |"
		// 		<< "|  	  - PgDown                           |"
		// 		<< "|  	                                     |"
		// 		<< "└----------------------------------------┘"
		while (!glfwWindowShouldClose(window)) {
			processInput(window, obj, windowInfo);

			glClearColor(windowInfo.BackgroundColors[0], windowInfo.BackgroundColors[1], windowInfo.BackgroundColors[2], 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			FrameImGui();
			if (windowInfo.showDebugWindow) {
				OptionImGui(obj, windowInfo, io);
			}

			if (obj.toggleRotation) {
				if (obj.rotation[1] >= 12.6f)
					obj.rotation[1] = 0.0f;
				obj.rotation[1] += 0.02f;
			}

			if (argc == 3) {
				glUseProgram(shader.shaderProgram);
				glUniform1i(glGetUniformLocation(shader.shaderProgram, "uUseTexture"), obj.toggleTexture);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture);
			}

			render(obj, VAO, modelLoc);

			renderImGui();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		ShutdownImGui();
		glfwTerminate();
	}
	catch(const std::exception& e) {
		std::cerr << RED << e.what() << RESET << '\n';
	}
	return 0;
}
