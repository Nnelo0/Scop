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

	if (TPressedLastFrame && !TPressedLastFrame) {
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
		unsigned int VAO, VBO, EBO;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		// -- VBO --
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, obj.vertices.size() *  sizeof(vertex), obj.vertices.data(), GL_STATIC_DRAW);
		// glEnableClientState(GL_VERTEX_ARRAY);
		// glVertexPointer(3, GL_FLOAT, sizeof(vertex), (void *)0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)0);
		glEnableVertexAttribArray(0);
		// obsolete
		//	glEnableClientState(GL_COLOR_ARRAY);
		//	glColorPointer(3, GL_FLOAT, sizeof(vertex), (void *)(3 * sizeof(float)));

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// -- EBO --
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		// glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj.faces.size() * sizeof(unsigned int), obj.faces.data(), GL_STATIC_DRAW);

		glBindVertexArray(0);

		// glMatrixMode(GL_PROJECTION);
		// glLoadIdentity();
		// gluPerspective(45.0, 1920.0 / 1080.0, 0.1, 100.0); // FOV, aspect, near, far

		double rotationAngle = 0.1;

		float identity[16] = {
		    1,0,0,0,
		    0,1,0,0,
		    0,0,1,0,
		    0,0,0,1
		};

		glUseProgram(shader.shaderProgram);

		GLint modelLoc = glGetUniformLocation(shader.shaderProgram, "uModel");
		GLint viewLoc = glGetUniformLocation(shader.shaderProgram, "uView");
		GLint projLoc = glGetUniformLocation(shader.shaderProgram, "uProjection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, identity);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, identity);
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, identity);
		while (!glfwWindowShouldClose(window)) {
			
			processInput(window, obj);

			glClearColor(0.8f ,0.3f, 0.69f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// glMatrixMode(GL_MODELVIEW);
			// glLoadIdentity();
			// glTranslatef(0.0f, 0.0f, -6.0f);

			glUseProgram(shader.shaderProgram);
			glBindVertexArray(VAO);
			// glPushMatrix();

			// glTranslatef(obj.position[0], obj.position[1], obj.position[2]);
			if (obj.toggleRotation) {
				rotationAngle += 0.05f;
			}

			// glTranslatef(obj.center_x, obj.center_y, obj.center_z);
			// glRotatef(rotationAngle * 30.0f, 0.0f, 1.0f, 0.0f);
			// glTranslatef(-obj.center_x, -obj.center_y, -obj.center_z);

			glDrawArrays(GL_TRIANGLES, 0, obj.vertices.size());

			//-- DEBUG --
			// glPointSize(20.0f);
			// glColor3f(1.0f, 0.0f, 0.0f);
			// glBegin(GL_POINTS);
			// 	glVertex3d(obj.center_x, obj.center_y, obj.center_z);
			// glEnd();
			//-- DEBUG --

			// glPopMatrix();

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
