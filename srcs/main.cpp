#include "all.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int heigth)
{
	(void)window;
	glViewport(0, 0, width, heigth);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void drawColoredFaces(const Obj &obj)
{
    glBegin(GL_TRIANGLES);

    for (size_t i = 0; i < obj.faces.size(); i += 3)
	{
	    const t_vertex &a = obj.verticesParse[obj.faces[i] - 1];
	    const t_vertex &b = obj.verticesParse[obj.faces[i+1] - 1];
	    const t_vertex &c = obj.verticesParse[obj.faces[i+2] - 1];

	    glColor3f(
	        (rand() % 100) / 100.0f,
	        (rand() % 100) / 100.0f,
	        (rand() % 100) / 100.0f
	    );

	    glVertex3f(a.x, a.y, a.z);
	    glVertex3f(b.x, b.y, b.z);
	    glVertex3f(c.x, c.y, c.z);
	}

    glEnd();
}

int main(int argc, char **argv)
{
	try
	{
		Obj obj(argv[1]);
		
		if (!glfwInit()) {
			std::cerr << "failed to init\n";
			return -1;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

		GLFWwindow *window = glfwCreateWindow(1920, 1080, "Scop", NULL, NULL);
		if (window == NULL) {
			std::cerr << "failed to create window\n";
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);

		if (glewInit() != GLEW_OK) {
			std::cerr << "failed to initialize GLAD\n";
			return -1;
		}

		glViewport(0, 0, 1920, 1080);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glEnable(GL_DEPTH_TEST);

		cout << "  0--------0\n" 
			 << " /|       /|\n"
			 << "0--------0 |\n" 
			 << "| |      | |\n" 
			 << "| 0------|-0\n"
			 << "|/       |/\n"
			 << "0--------0 \n";

		/*	
			VAO (Vertex Array Object) -> all config, which VBO/EBO use...
			VBO (Vertex Buffer Object) -> (x, y, z)
			EBO (Element Buffer Objet) -> (1, 2, 5) stock index of vertex to draw triangles
		*/
		unsigned int VAO, VBO, EBO;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		// -- VBO --
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, obj.vertices.size() * sizeof(float), obj.vertices.data(), GL_STATIC_DRAW);

		// -- EBO --
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj.faces.size() * sizeof(unsigned int), obj.faces.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90.0, 1920.0 / 1080.0, 0.1, 100.0); // FOV, aspect, near, far
			
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -3.0f);

		double rotationAngle = 0.1;
		while (!glfwWindowShouldClose(window)) {
			rotationAngle += 0.1f;
			processInput(window);
			
			glClearColor(0.8f ,0.3f, 0.69f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(0.0f, 0.0f, -6.0f);
			glRotatef(rotationAngle * 30.0f, 0.0f, 1.0f, 0.0f);

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, obj.faces.size(), GL_UNSIGNED_INT, 0);

			// drawColoredFaces(obj);

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
