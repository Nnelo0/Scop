#include "all.hpp"

/*
	VAO (Vertex Array Object) -> all config, which VBO/EBO use...
	VBO (Vertex Buffer Object) -> (x, y, z)
	EBO (Element Buffer Objet) -> (1, 2, 5) stock index of vertex to draw triangles
*/


unsigned int initBuffers(Obj &obj)
{
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

	return VAO;
}

GLint matrixParameters(Shaders &shader)
{
	glUseProgram(shader.shaderProgram);

	Matrix proj = Matrix::perspective(90.0f, 1920.0f / 1080.0f, 0.1f, 102400); // FOV, aspect, near, far
	Vec3 eye(0.0f, 0.0f, 7.0f), center(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f);
	Matrix view = Matrix::lookAt(eye, center, up);

	GLint modelLoc = glGetUniformLocation(shader.shaderProgram, "uModel");
	GLint viewLoc = glGetUniformLocation(shader.shaderProgram, "uView");
	GLint projLoc = glGetUniformLocation(shader.shaderProgram, "uProjection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.data());
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, proj.data());

	return modelLoc;
}

void render(Obj &obj, unsigned int &VAO, GLint &modelLoc)
{
	Matrix Tpos = Matrix::translate(obj.position[0], obj.position[1], obj.position[2]);
	Matrix Tcenter = Matrix::translate(obj.centerX, obj.centerY, obj.centerZ);
	Matrix Rx = Matrix::rotateX(obj.rotation[0]);
	Matrix Ry = Matrix::rotateY(obj.rotation[1]);
	Matrix Rz = Matrix::rotateZ(obj.rotation[2]);
	Matrix model = Tpos * Tcenter * Rx * Ry * Rz * Matrix::translate(-obj.centerX, -obj.centerY, -obj.centerZ);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.data());
	glBindVertexArray(VAO);
	
	glDrawArrays(GL_TRIANGLES, 0, obj.vertices.size());
}