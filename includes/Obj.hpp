#pragma once
#include "all.hpp"

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
	private:
		string name;
		string nameMtl;
		string sMode;

	public:

		vector<vertex> verticesParse;
		vector<face> facesParse;
		vector<unsigned int> faces;
		vector<vertex> vertices;

		float	position[3] = {0.0f, 0.0f, 0.0f};
		float	rotation[3] = {0.0f, 0.0f, 0.0f};
		bool	toggleRotation = true;
		bool	toggleTexture = false;
		float	centerX, centerY, centerZ;

	public:
		Obj(string filename);
		~Obj();

		void generateUVs(vector<vertex> &verts);
};
