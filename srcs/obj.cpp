#include "Obj.hpp"

vertex Obj::getVertexFromVertices(int idx)
{
	if (verticesParse.size() < idx) {
		out_of_range("Invalid idx for face");
	}
	return verticesParse[idx];
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
			t_vertex tmp;
			for (size_t i = 0; i < 3; i++) {
				if (i != 2 && line.find_first_of(' ') == string::npos) throw runtime_error("Failed to read Vertex -> " + line + '!');
				string tmpValue = line.substr(0, line.find_first_of(' '));
				line.erase(0, line.find_first_of(' ') + 1);
				for (size_t j = 0; line[j]; j++) {
					if (!isdigit(line[j]) && (line[j] != '-' && line[j] != '.' && line[j] != ' '))  { cout << "line[j] ["<< line[j] << "]\n"; throw runtime_error("Failed to read Vertex-> " + line + '!'); }
				}

				double value = atof(tmpValue.c_str());
				vertices.push_back(value);
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
			verticesParse.push_back(tmp);
		}

		if (line.find_first_of('s') == 0 && line.find_first_of(' ') == 1) {
			sMode = line.substr(2, line.length());
			cout << "[DEBUG] : S -> " + sMode << endl;
		}

		if (line.find_first_of('f') == 0 && line.find_first_of(' ') == 1) {
			line.erase(0, 2);
			t_face tmpFace;
			for (size_t i = 0; i < 4; i++) {
				if (line.empty()) continue;
				if (i < 2 && line.find_first_of(' ') == string::npos) throw runtime_error("Failed to read Face -> " + line + '!');
				string tmpValue = line.substr(0, line.find_first_of(' '));
				line.erase(0, strlen(tmpValue.c_str()) + 1);
				for (size_t j = 0; line[j]; j++) {
					if (!isdigit(line[j]) && (line[j] != '-' && line[j] != '.' && line[j] != ' '))  { cout << "line[j] ["<< line[j] << "]\n"; throw runtime_error("Failed to read Face -> " + line + '!'); }
				}

				double idx = atof(tmpValue.c_str());
				if (idx <= 0)
					throw runtime_error("Failed to read Face -> " + line + '!');
				faces.push_back(idx);
				switch (i) {
					case 0:
						tmpFace.v1 = idx;
						tmpFace.vertexCount++;
						break;
					case 1:
						tmpFace.v2 = idx;
						tmpFace.vertexCount++;
						break;
					case 2:
						tmpFace.v3 = idx;
						tmpFace.vertexCount++;
						break;
					case 3:
						tmpFace.v4 = idx;
						tmpFace.vertexCount++;
						break;
				}
			}
			cout << "[DEBUG] : f " << " -> " << tmpFace.v1 << ", " << tmpFace.v2 << ", " << tmpFace.v3 << ", " << tmpFace.v4 << "\n";
			cout << "[DEBUG] : f v -> " << tmpFace.vertexCount << "\n";
			facesParse.push_back(tmpFace);
		}
	}
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

Obj::~Obj()
{
}