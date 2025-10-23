#include "all.hpp"

int main(int argc, char **argv)
{
	try
	{
		Obj obj(argv[1]);
		if (!obj.hasTexture) {
			obj.generateUVs(obj.vertices);
		}

		if (!glfwInit()) {
			std::cerr << "failed to init\n";
			return -1;
		}

		Camera camera;
		WindowInfo windowInfo;
		initWindowInfo(windowInfo);
		GLFWwindow *window = initWindow(obj.name, camera);

		ImGuiIO& io = initImGui(window);

		unsigned int VAO = initBuffers(obj);
		glBindVertexArray(0);

		Shaders shader("shaders/vertex.vert", "shaders/fragment.frag");
		matrixParameters(shader);

		GLuint texture;
		if (argc == 3) {
			texture = loadTexture(argv[2]);
			obj.hasTexture = true;
			glUniform1i(glGetUniformLocation(shader.shaderProgram, "uUseTexture"), 0);
		}

		cout	<< "┌----------------------------------------┐\n"
				<< "|                Commands                |\n"
				<< "|  Object Movements :                    |\n"
				<< "|     - ↑ : Move Forward                 |\n"
				<< "|     - ↓ : Move Backward                |\n"
				<< "|     - → : Move Right                   |\n"
				<< "|     - ← : Move Left                    |\n"
				<< "|     - PgUp : Move Up                   |\n"
				<< "|     - PgDown : Move Down               |\n"
				<< "|     - LEFT_SHIFT : x2 speed            |\n"
				<< "|                                        |\n"
				<< "|   Camera Movements :                   |\n"
				<< "|     - W : Move Forward                 |\n"
				<< "|     - A : Move Backward                |\n"
				<< "|     - S : Move Right                   |\n"
				<< "|     - D : Move Left                    |\n"
				<< "|     - Space : Move Up                  |\n"
				<< "|     - Left_Ctrl : Move Down            |\n"
				<< "|     - LEFT_SHIFT : x2 speed            |\n"
				<< "|                                        |\n"
				<< "|   Tools :                              |\n"
				<< "|     - R : Reset Object                 |\n"
				<< "|     - C : Reset Camera                 |\n"
				<< "|     - P : Stop auto-rotation           |\n"
				<< "|     - TAB : Open Gui                   |\n"
				<< "└----------------------------------------┘\n";

		while (!glfwWindowShouldClose(window)) {
			processInput(window, obj, camera, windowInfo);

			glClearColor(windowInfo.BackgroundColors[0], windowInfo.BackgroundColors[1], windowInfo.BackgroundColors[2], 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			FrameImGui();
			if (windowInfo.showDebugWindow) {
				OptionImGui(obj, camera, windowInfo, io, argc);
			}

			if (obj.toggleRotation) {
				if (obj.rotation[0] >= 12.6f)
						obj.rotation[0] = 0.0f;
				if (obj.rotation[1] >= 12.6f)
						obj.rotation[1] = 0.0f;
				if (obj.rotation[2] >= 12.6f)
						obj.rotation[2] = 0.0f;

				if (obj.autoRotate == 0)
					obj.rotation[0] += 0.02f;
				if (obj.autoRotate == 1)
					obj.rotation[1] += 0.02f;
				if (obj.autoRotate == 2)
					obj.rotation[2] += 0.02f;
			}

			if (argc == 3) {
				glUseProgram(shader.shaderProgram);
				glUniform1i(glGetUniformLocation(shader.shaderProgram, "uUseTexture"), obj.toggleTexture);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture);
			}

			Matrix view = camera.getViewMatrix();
			GLint viewLoc = glGetUniformLocation(shader.shaderProgram, "uView");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.data());

			render(obj, VAO, shader);

			renderImGui();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		ShutdownImGui();
		glfwTerminate();
	}
	catch(const std::logic_error& e) {
		std::cerr << "Error : Parameters can't be null" << '\n';
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	return 0;
}
