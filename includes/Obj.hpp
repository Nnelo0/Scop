#pragma once
#include "all.hpp"

typedef struct vertex
{
	float x,y,z;
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

		vector<vertex> vertices;
		vector<face> faces;
	public:
		Obj(string filename);
		vertex getVertexFromVertices(int idx);
		~Obj();
};
