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

		double	position[3] = {0.0, 0.0, 0.0};
		bool	toggleRotation = true;
		bool	toggleTexture = false;
		float	center_x, center_y, center_z;

	public:
		Obj(string filename);
		~Obj();

		void generateUVs(vector<vertex> &verts);
};
