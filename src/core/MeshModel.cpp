#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

#include "Raytracer.h"

// from https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ
static void load_obj(const std::string& filename, vector<glm::vec3> &vertices,
					 vector<glm::vec3> &normals, vector<unsigned int> &elements, vector<unsigned int> &normal_elements)
{
	std::ifstream in(filename, std::ios::in);
	if (!in) {
		std::cerr << "Cannot open " << filename << std::endl;
		std::exit(1);
	}

	std::string line;
	while (std::getline(in, line))
	{
		if (line.substr(0, 2) == "v ") {
			std::istringstream s(line.substr(2));
			glm::vec3 v;
			s >> v.x;
			s >> v.y;
			s >> v.z;
			vertices.push_back(v);
		} else if (line.substr(0, 3) == "vn ") {
			std::istringstream s(line.substr(2));
			glm::vec3 v;
			s >> v.x;
			s >> v.y;
			s >> v.z;
			normals.push_back(v);
		} else if (line.substr(0, 2) == "f ") {
			std::istringstream s(line.substr(2));
			unsigned int a, b, c, dump;
			unsigned int na, nb, nc;
			char slash;
			s >> a;
			s >> slash;
			s >> dump;
			s >> slash;
			s >> na;
			s >> b;
			s >> slash;
			s >> dump;
			s >> slash;
			s >> nb;
			s >> c;
			s >> slash;
			s >> dump;
			s >> slash;
			s >> nc;
			a--;
			b--;
			c--;
			na--;
			nb--;
			nc--;
			elements.push_back(a);
			elements.push_back(b);
			elements.push_back(c);
			normal_elements.push_back(na);
			normal_elements.push_back(nb);
			normal_elements.push_back(nc);
		} else if (line[0] == '#') {
			/* ignoring this line */
		}
	}
}

MeshModel::MeshModel(const std::string& filename) {
	load_obj(filename, vertices, normals, elements, normal_elements);
	min = glm::vec3(std::numeric_limits<float>::max());
	max = glm::vec3(std::numeric_limits<float>::min());
	for (glm::vec3 pos : vertices) {
		min = glm::min(min, pos);
		max = glm::max(max, pos);
	}
}

