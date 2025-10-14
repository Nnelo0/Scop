#pragma once
#include "all.hpp"
typedef struct vertex
{
	float x,y,z;
} t_vertex;

typedef struct face
{
	t_vertex v[4];
	int vertexCount;
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

vertex Obj::getVertexFromVertices(int idx)
{
	if (vertices.size() < idx) {
		out_of_range("Invalid idx for face");
	}
	return vertices[idx];
}

Obj::Obj(string filename)
{
	string line;
	ifstream objFile(filename);
	if (!objFile)
		throw runtime_error("Failed to read " + filename + '!');

	while (getline(objFile, line)) {
		if (line.find_first_of('#') != string::npos) {
			line = line.substr(0, line.find_first_of('#'));
		}
		cout << "[DEBUG] : line -> [" + line + ']' << endl;

		if (line.find("mtllib") != string::npos) {
			nameMtl = line.substr(strlen("mtllib"), line.length());
			cout << "[DEBUG] : nameMtl -> " + nameMtl << endl;
		}

		if (line.find_first_of('o') == 0  && line.find_first_of(' ') == 1) {
			name = line.substr(1, line.length());
			cout << "[DEBUG] : name -> " + name << endl;
		}

		if (line.find_first_of('v') == 0 && line.find_first_of(' ') == 1) {
			line.erase(0, 2);
			// cout << "[DEBUG] : line V -> [" + line + ']' << endl;
			t_vertex tmp;
			for (size_t i = 0; i < 3; i++) {
				if (i != 2 && line.find_first_of(' ') == string::npos) throw runtime_error("Failed to read Vertex -> " + line + '!');
				string tmpValue = line.substr(0, line.find_first_of(' '));
				// cout << "[DEBUG] : tmpValue -> [" + tmpValue + ']' << endl;
				line.erase(0, line.find_first_of(' ') + 1);
				// cout << "[DEBUG] : line V2 -> [" + line + ']' << endl;
				for (size_t j = 0; line[j]; j++) {
					if (!isdigit(line[j]) && (line[j] != '-' && line[j] != '.' && line[j] != ' '))  { cout << "line[j] ["<< line[j] << "]\n"; throw runtime_error("Failed to read Vertex-> " + line + '!'); }
				}

				double value = atof(tmpValue.c_str());
				switch (i) {
					case 0:
						tmp.x = value;
						break;
					case 1:
						tmp.y = value;
						break;
					case 2:
						tmp.z = value;
						break;
				}
			}
			vertices.push_back(tmp);
		}

		if (line.find_first_of('s') == 0 && line.find_first_of(' ') == 1) {
			sMode = line.substr(2, line.length());
			cout << "[DEBUG] : S -> " + sMode << endl;
		}

		if (line.find_first_of('f') == 0 && line.find_first_of(' ') == 1) {
			line.erase(0, 2);
			// cout << "[DEBUG] : line F -> [" + line + ']' << endl;
			t_face tmpFace;
			for (size_t i = 0; i < 4; i++) {
				if (line.empty()) continue;
				if (i < 2 && line.find_first_of(' ') == string::npos) throw runtime_error("Failed to read Face -> " + line + '!');
				string tmpValue = line.substr(0, line.find_first_of(' '));
				cout << "[DEBUG] : tmpValue -> [" + tmpValue + ']' << endl;
				line.erase(0, strlen(tmpValue.c_str()) + 1);
				cout << "[DEBUG] : line F2 -> [" + line + ']' << endl;
				for (size_t j = 0; line[j]; j++) {
					if (!isdigit(line[j]) && (line[j] != '-' && line[j] != '.' && line[j] != ' '))  { cout << "line[j] ["<< line[j] << "]\n"; throw runtime_error("Failed to read Face -> " + line + '!'); }
				}

				double idx = atof(tmpValue.c_str());
				cout << "IDX : "<< idx << endl;
				switch (i) {
					case 0:
						tmpFace.v[0] = getVertexFromVertices(idx);
						tmpFace.vertexCount++;
						break;
					case 1:
						tmpFace.v[1] = getVertexFromVertices(idx);
						tmpFace.vertexCount++;
						break;
					case 2:
						tmpFace.v[2] = getVertexFromVertices(idx);
						tmpFace.vertexCount++;
						break;
					case 3:
						tmpFace.v[3] = getVertexFromVertices(idx);
						tmpFace.vertexCount++;
						break;
				}
			}
			cout << "[DEBUG] : f v1" << " -> " << tmpFace.v[0].x << ", " << tmpFace.v[0].y << ", " << tmpFace.v[0].z  << "\n";
			cout << "[DEBUG] : f v2" << " -> " << tmpFace.v[1].x << ", " << tmpFace.v[1].y << ", " << tmpFace.v[1].z  << "\n";
			cout << "[DEBUG] : f v3" << " -> " << tmpFace.v[2].x << ", " << tmpFace.v[2].y << ", " << tmpFace.v[2].z  << "\n";
			cout << "[DEBUG] : f v4" << " -> " << tmpFace.v[3].x << ", " << tmpFace.v[3].y << ", " << tmpFace.v[3].z  << "\n";

			faces.push_back(tmpFace);
		}

	}
	if (nameMtl.empty()) {
		cout << "[DEBUG] : Failed to found .mtl\n";
	}
	if (name.empty()) {
		cout << "[DEBUG] : Failed to found .mtl\n";
	}

	int j = 0;

	for (auto i = vertices.begin(); i != vertices.end(); i++)
	{
		cout << "v" << j << " -> " << (*i).x << ", " << (*i).y << ", " << (*i).z << "\n";
		j++;
	}
	
	j = 0;

	for (auto i = faces.begin(); i != faces.end(); i++)
	{
		cout << "f" << j << " -> " << (*i).v[0].x << ", " << (*i).v[1].x << ", " << (*i).v[2].x  << ", " << (*i).v[3].x << "\n";
		j++;
	}

	objFile.close();
}

Obj::~Obj()
{
}
