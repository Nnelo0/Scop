#include "Obj.hpp"

Obj::Obj(string filename)
{
	string line;
	ifstream objFile(filename);
	if (!objFile)
		throw runtime_error("Failed to read " + filename + '!');

	int nextColors = 'b';
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
			t_vertex tmp;
			for (size_t i = 0; i < 3; i++) {
				if (i != 2 && line.find_first_of(' ') == string::npos) throw runtime_error("Failed to read Vertex -> " + line + '!');
				string tmpValue = line.substr(0, line.find_first_of(' '));
				line.erase(0, line.find_first_of(' ') + 1);
				for (size_t j = 0; line[j]; j++) {
					if (!isdigit(line[j]) && (line[j] != '-' && line[j] != '.' && line[j] != ' '))  { cout << "line[j] ["<< line[j] << "]\n"; throw runtime_error("Failed to read Vertex-> " + line + '!'); }
				}

				double value = atof(tmpValue.c_str());
				switch (i) {
					case 0:
						tmp.x = value;
						tmp.r = 0.0f;
						break;
					case 1:
						tmp.y = value;
						tmp.g = 0.0f;
						break;
					case 2:
						tmp.z = value;
						tmp.b = 0.0f;
						break;
				}
			}
			verticesParse.push_back(tmp);
		}

		if (line.find_first_of('s') == 0 && line.find_first_of(' ') == 1) {
			sMode = line.substr(2, line.length());
			cout << "[DEBUG] : S -> " + sMode << endl;
		}

		if (line.find_first_of('f') == 0 && line.find_first_of(' ') == 1) {
			line.erase(0, 2);
			t_face tmpFace;
			float colors;
			switch (nextColors)
			{
				case 'b':
					colors = 0.2f;
					nextColors = 'g';
					break;
				case 'g':
					colors = 0.3f;
					nextColors = 'l';
					break;
				case 'l':
					colors = 0.4f;
					nextColors = 'b';
					break;
			}
			for (size_t i = 0; i < 4; i++) {
				if (line.empty()) continue;
				if (i < 2 && line.find_first_of(' ') == string::npos) throw runtime_error("Failed to read Face -> " + line + '!');
				string tmpValue = line.substr(0, line.find_first_of(' '));
				line.erase(0, strlen(tmpValue.c_str()) + 1);
				for (size_t j = 0; line[j]; j++) {
					if (!isdigit(line[j]) && (line[j] != '-' && line[j] != '.' && line[j] != ' '))  { cout << "line[j] ["<< line[j] << "]\n"; throw runtime_error("Failed to read Face -> " + line + '!'); }
				}

				double idx = atof(tmpValue.c_str()) - 1;
				if (idx < 0)
					throw runtime_error("Failed to read Face -> " + line + '!');
				if (tmpFace.vertexCount != 3)
					faces.push_back(idx);
				t_vertex tmpVertices;
				switch (i) {
					case 0:
						tmpFace.v1 = idx;
						tmpFace.vertexCount++;

						tmpVertices = verticesParse[tmpFace.v1];
						tmpVertices.r = colors;
						tmpVertices.g = colors;
						tmpVertices.b = colors;

						vertices.push_back(tmpVertices);
						break;
					case 1:
						tmpFace.v2 = idx;
						tmpFace.vertexCount++;

						tmpVertices = verticesParse[tmpFace.v2];
						tmpVertices.r = colors;
						tmpVertices.g = colors;
						tmpVertices.b = colors;
						vertices.push_back(tmpVertices);
						break;
					case 2:
						tmpFace.v3 = idx;
						tmpFace.vertexCount++;

						tmpVertices = verticesParse[tmpFace.v3];
						tmpVertices.r = colors;
						tmpVertices.g = colors;
						tmpVertices.b = colors;
						vertices.push_back(tmpVertices);
						break;
					case 3:
						tmpFace.v4 = idx;
						tmpFace.vertexCount++;
						break;
				}
			}
			t_vertex tmpVertices;
			if (tmpFace.vertexCount == 4) {
				faces.push_back(tmpFace.v1);
				faces.push_back(tmpFace.v4);
				faces.push_back(tmpFace.v3);

				switch (nextColors)
				{
					case 'b':
						colors = 0.2f;
						nextColors = 'g';
						break;
					case 'g':
						colors = 0.3f;
						nextColors = 'l';
						break;
					case 'l':
						colors = 0.4f;
						nextColors = 'b';
						break;
				}

				tmpVertices = verticesParse[tmpFace.v1];
				tmpVertices.r = colors;
				tmpVertices.g = colors;
				tmpVertices.b = colors;
				vertices.push_back(tmpVertices);
				tmpVertices = verticesParse[tmpFace.v4];
				tmpVertices.r = colors;
				tmpVertices.g = colors;
				tmpVertices.b = colors;
				vertices.push_back(tmpVertices);
				tmpVertices = verticesParse[tmpFace.v3];
				tmpVertices.r = colors;
				tmpVertices.g = colors;
				tmpVertices.b = colors;
				vertices.push_back(tmpVertices);
				cout << "[DEBUG] : IDX1 -> " << tmpFace.v4 << ", IDX2 -> " << tmpFace.v3 << ", IDX3 -> " << tmpFace.v2 << endl;
			}

			cout << "[DEBUG] : f -> " << tmpFace.v1 << ", " << tmpFace.v2 << ", " << tmpFace.v3 << ", " << tmpFace.v4 << "\n";
			cout << "[DEBUG] : f v -> " << tmpFace.vertexCount << "\n";
			facesParse.push_back(tmpFace);

		}
	}

	float allx = 0, ally = 0, allz = 0;
	float count = 0;
	for (auto i = verticesParse.begin(); i != verticesParse.end(); i++) {
		allx += (*i).x;
		ally += (*i).y;
		allz += (*i).z;
		count++;
	}

	centerX = allx / count;
	centerY = ally / count;
	centerZ = allz / count;
	cout << "[DEBUG] : centerx with barycenter -> " << centerX << "\n";
	cout << "[DEBUG] : centery with barycenter -> " << centerY << "\n";
	cout << "[DEBUG] : centerz with barycenter -> " << centerZ << "\n";

	if (nameMtl.empty()) {
		cout << "[DEBUG] : Failed to found .mtl\n";
	}
	if (name.empty()) {
		cout << "[DEBUG] : Failed to found .mtl\n";
	}

	if (facesParse.empty() || verticesParse.empty() || faces.empty() || vertices.empty())
		throw runtime_error("Failed to parse .obj files");

	objFile.close();
}

Obj::~Obj() {}

Vec3 computeNormal(vertex a, vertex b, vertex c)
{
	Vec3 u = {b.x - a.x, b.y - a.y, b.z - a.z};
	Vec3 v = {c.x - a.x, c.y - a.y, c.z - a.z};

	return Vec3::cross(u, v).normalized();
}

void Obj::generateUVs(vector<vertex> &verts)
{

	float minX = FLT_MAX, maxX = -FLT_MAX;
	float minY = FLT_MAX, maxY = -FLT_MAX;
	float minZ = FLT_MAX, maxZ = -FLT_MAX;
	for (auto &v : verts) {
		if (v.x < minX) minX = v.x;
		if (v.x > maxX) maxX = v.x;
		if (v.y < minY) minY = v.y;
		if (v.y > maxY) maxY = v.y;
		if (v.z < minZ) minZ = v.z;
		if (v.z > maxZ) maxZ = v.z;
	}

	float sizeX = maxX - minX;
	float sizeY = maxY - minY;
	float sizeZ = maxZ - minZ;

	for (size_t i = 0; i < verts.size(); i += 3) {
		vertex &a = verts[i];
		vertex &b = verts[i + 1];
		vertex &c = verts[i + 2];

		Vec3 n = computeNormal(a, b ,c);
		float absX = fabs(n.x);
		float absY = fabs(n.y);
		float absZ = fabs(n.z);

		for (vertex *v : {&a, &b, &c}) {
			if (absX >= absY && absX >= absZ) {
				v->u = (v->z - minZ) / sizeZ;
				v->v = (v->y - minY) / sizeY;
			}
			else if (absY >= absX && absY >= absZ) {
				v->u = (v->x - minX) / sizeX;
				v->v = (v->z - minZ) / sizeZ;
			}
			else {
				v->u = (v->x - minX) / sizeX;
				v->v = (v->y - minX) / sizeZ;
			}
		}
	}

}
