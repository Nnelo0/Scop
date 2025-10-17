#version 460 core

in vec3 vertexColor;
in vec2 vertexTex;

out vec4 FragColor;

uniform sampler2D uTexture;
uniform bool uUseTexture;

void main()
{
	if (uUseTexture)
		FragColor = texture(uTexture, vertexTex);
	else
		FragColor = vec4(vertexColor, 1.0); 
}