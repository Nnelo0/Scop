#pragma once
#include "all.hpp"

typedef struct vt
{
	float u, v;
} t_vt;

typedef struct vertex
{
	float x,y,z;
	float r, g, b;
	float u, v;
} t_vertex;

typedef struct face
{
	unsigned int v1, v2, v3, v4 = 0;
	int vertexCount = 0;
} t_face;

class Obj
{

	public:

		string name;
		vector<vertex> verticesParse;
		vector<face> facesParse;
		vector<unsigned int> faces;
		vector<vertex> vertices;
		vector<vt> vts;

		float	position[3] = {0.0f, 0.0f, 0.0f};
		float	rotation[3] = {0.0f, 0.0f, 0.0f};
		bool	toggleRotation = true;
		bool	toggleTexture = false;
		float	centerX, centerY, centerZ;
		bool	hasTexture = false;
		long	triangleCount;
		float	speed;
		float	defaultSpeed[1] = {0.2f};
		int		autoRotate;

	public:
		Obj(string filename);
		~Obj();

		void	generateUVs(vector<vertex> &verts);
		void	objectInput(GLFWwindow *window, WindowInfo &windowInfo);
};

