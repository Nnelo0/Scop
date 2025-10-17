#version 460 core

layout(location = 0) in vec3 aPos; // pos of vertex
layout(location = 1) in vec3 aColor; // color of vertex
layout(location = 2) in vec2 aTex; // texture of vertex

//matrices
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 vertexColor;
out vec2 vertexTex;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);

	vertexColor = aColor;
	vertexTex = aTex;
}