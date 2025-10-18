#include "all.hpp"

bool	spacePressedLastFrame = false;
bool	TPressedLastFrame = false;

void framebuffer_size_callback(GLFWwindow *window, int width, int heigth)
{
	(void)window;
	glViewport(0, 0, width, heigth);
}

void processInput(GLFWwindow *window, Obj &obj)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) obj.position[0] -= 0.2;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) obj.position[0] += 0.2;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) obj.position[1] += 0.2;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) obj.position[1] -= 0.2;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) obj.position[2] += 0.2;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) obj.position[2] -= 0.2;
	bool SpacePressedNow = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
	bool TPressedNow = glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS;

	if (SpacePressedNow && !spacePressedLastFrame) {
		obj.toggleRotation = !obj.toggleRotation;
	}

	if (TPressedNow && !TPressedLastFrame) {
		obj.toggleTexture = !obj.toggleTexture;
	}

	TPressedLastFrame = TPressedNow;
	spacePressedLastFrame = SpacePressedNow;
}

int main(int argc, char **argv)
{
	try
	{
		Obj obj(argv[1]);
		obj.generateUVs(obj.vertices);
		cout << "[DEBUG] faces -> \n";
		int j = 0;
		for (auto i = obj.faces.begin(); i != obj.faces.end(); i++)
		{
			if (j == 3) {cout << "\n"; j = 0;}
			cout << (*i) << ", ";
			j++;
		}
		cout << '\n';
		
		cout << "[DEBUG] vertex -> \n";
		for (auto i = obj.verticesParse.begin(); i != obj.verticesParse.end(); i++)
		{
			cout << "{coords: " << (*i).x << ", " << (*i).y << ", " << (*i).z << " } {colors: " << (*i).r << ", " << (*i).g << ", " << (*i).b << " }";
			cout << '\n';
		}
		cout << '\n';
		
		cout << "[DEBUG] new vertex -> \n";
		for (auto i = obj.vertices.begin(); i != obj.vertices.end(); i++)
		{
			cout << "{coords: " << (*i).x << ", " << (*i).y << ", " << (*i).z << " } {colors: " << (*i).r << ", " << (*i).g << ", " << (*i).b << " }";
			cout << '\n';
		}
		
		if (!glfwInit()) {
			std::cerr << "failed to init\n";
			return -1;
		}
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
		GLFWwindow *window = glfwCreateWindow(1920, 1080, "Scop", NULL, NULL);
		if (window == NULL) {
			std::cerr << "failed to create window\n";
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);

		if (glewInit() != GLEW_OK) {
			std::cerr << "failed to initialize Glew\n";
			return -1;
		}

		glViewport(0, 0, 1920, 1080);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glEnable(GL_DEPTH_TEST);

		Shaders shader("shaders/vertex.vert", "shaders/fragment.frag");

		/*
			VAO (Vertex Array Object) -> all config, which VBO/EBO use...
			VBO (Vertex Buffer Object) -> (x, y, z)
			EBO (Element Buffer Objet) -> (1, 2, 5) stock index of vertex to draw triangles
		*/
		unsigned int VAO, VBO;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		// -- VBO --
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, obj.vertices.size() *  sizeof(vertex), obj.vertices.data(), GL_STATIC_DRAW);

		//vertex
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)0);
		glEnableVertexAttribArray(0);

		//color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// UV textures
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);

		double rotationAngle = 0.1;

		glUseProgram(shader.shaderProgram);

		Matrix proj = Matrix::perspective(90.0f, 1920.0f / 1080.0f, 0.1f, 1024); // FOV, aspect, near, far
		Vec3 eye(0.0f, 0.0f, 10.0f), center(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f);
		Matrix view = Matrix::lookAt(eye, center, up);

		GLint modelLoc = glGetUniformLocation(shader.shaderProgram, "uModel");
		GLint viewLoc = glGetUniformLocation(shader.shaderProgram, "uView");
		GLint projLoc = glGetUniformLocation(shader.shaderProgram, "uProjection");

		Matrix identity = Matrix::identity();
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, identity.data());
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.data());
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, proj.data());

		GLuint texture;
		if (argc == 3) {
			texture = loadTexture(argv[2]);
			glUniform1i(glGetUniformLocation(shader.shaderProgram, "uUseTexture"), 0);
		}

		while (!glfwWindowShouldClose(window)) {
			// if (obj.toggleTexture) {
			// 	cout << "[DEBUG] : Texture actived" << endl;
			// } else {
			// 	cout << "[DEBUG] : Texture disabled" << endl;
			// }

			processInput(window, obj);

			glClearColor(0.4f ,0.3f, 0.69f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (obj.toggleRotation) {
				rotationAngle += 0.02f;
			}

			if (argc == 3) {
				glUseProgram(shader.shaderProgram);
				glUniform1i(glGetUniformLocation(shader.shaderProgram, "uUseTexture"), obj.toggleTexture);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture);
			}

			// cout << "[DEBUG] : VIEW -> \n" << view << endl;
			// cout << "[DEBUG] : POS -> " << obj.position[0] << ", " <<  obj.position[1] << ", " << obj.position[2] << endl;
			Matrix Tpos = Matrix::translate(obj.position[0], obj.position[1], obj.position[2]);
			Matrix Tcenter = Matrix::translate(obj.centerX, obj.centerY, obj.centerZ);
			Matrix R = Matrix::rotateY(rotationAngle);
			Matrix model = Tpos * Tcenter * R * Matrix::translate(-obj.centerX, -obj.centerY, -obj.centerZ);

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.data());

			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, obj.vertices.size());

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwTerminate();
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << '\n';
	}
	return 0;
}
