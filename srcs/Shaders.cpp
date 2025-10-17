#include "Shaders.hpp"

string Shaders::readShaderFile(string filePath)
{
	stringstream buf;
	ifstream file(filePath);
	if (!file) {
		throw runtime_error("Failed to read shader file -> [" + filePath + "]");
	}

	buf << file.rdbuf();
	return buf.str();
}

Shaders::Shaders(string vertexFilePath, string fragmentFilePath)
{
	string vertexBuff = readShaderFile(vertexFilePath);
	string fragmentBuff= readShaderFile(fragmentFilePath);
	
	GLuint vertexShader = compileShader(vertexBuff, GL_VERTEX_SHADER);
	GLuint fragmentshader = compileShader(fragmentBuff, GL_FRAGMENT_SHADER);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentshader);
	glLinkProgram(shaderProgram);

	GLint succes;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &succes);
	if (!succes) {
		string log(1024, '\0');
		glGetProgramInfoLog(shaderProgram, 1024, nullptr, (GLchar *)log.data());
		throw runtime_error("Failed to link shader log -> \n" + log);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentshader);
}

GLuint Shaders::compileShader(string fileBuf, GLenum type)
{
	GLuint shader = glCreateShader(type);
	const char *src = fileBuf.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	GLint succes;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);
	if (!succes) {
		string log(1024, '\0');
		glGetShaderInfoLog(shader, 1024, nullptr, (GLchar *)log.data());
		throw runtime_error("Failed to compile shader log -> \n" + log);
	}

	return shader;
}

Shaders::~Shaders()
{

}