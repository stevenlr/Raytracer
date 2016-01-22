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
	while (std::getline(in, line)) {
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

static bool intersectTriangle(const Ray& ray, const glm::vec3& v0, const glm::vec3& v1,
                              const glm::vec3& v2, float& distHit, float& alpha, float& beta)
{
	glm::mat3 M(v1 - v0, v2 - v0, -ray.dir);
	if (glm::determinant(M) == 0)
		return false;

	glm::vec3 b = glm::vec3(ray.orig) - v0;
	glm::vec3 r = glm::inverse(M) * b;
	if (r[0] >= 0 && r[1] >= 0 && r[0] + r[1] <= 1) {
		alpha = r[0];
		beta = r[1];
		distHit = r[2];
		return true;
	}

	return false;
}

class MeshTriangle : public Object
{
public:
	glm::vec3 v0;
	glm::vec3 v1;
	glm::vec3 v2;
	glm::vec3 n0;
	glm::vec3 n1;
	glm::vec3 n2;

	MeshTriangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 n0, glm::vec3 n1, glm::vec3 n2) :
		Object(Material()), v0(v0), v1(v1), v2(v2), n0(n0), n1(n1), n2(n2)
	{
		glm::vec3 min = glm::min(v0, glm::min(v1, v2));
		glm::vec3 max = glm::max(v0, glm::max(v1, v2));
		aabb = AABB(min, max);
		computed = true;
	}

	virtual bool intersect(Ray ray, Hit &hit) const
	{
		float dist;
		float alpha;
		float beta;
		if (intersectTriangle(ray, v0, v1, v2, dist, alpha, beta)
			&& dist < ray.tMax && dist >= ray.tMin && dist <= hit.t) {
			glm::vec3 normal = glm::normalize((1 - alpha - beta) * n0 + alpha * n1 + beta * n2);
			float t = dist;
			hit.t = t;
			hit.reached = true;
			hit.pos = ray(t);
			hit.normal = normal;
			hit.transform(transform);
			return true;
		}

		return false;
	}
};

MeshModel::MeshModel(const std::string& filename)
{
	load_obj(filename, vertices, normals, elements, normal_elements);

	min = glm::vec3(std::numeric_limits<float>::max());
	max = glm::vec3(std::numeric_limits<float>::min());
	for (glm::vec3 pos : vertices) {
		min = glm::min(min, pos);
		max = glm::max(max, pos);
	}

	std::list<Object*> objects;
	for (size_t i = 0; i < elements.size(); i += 3) {
		const glm::vec3& v0 = vertices[elements[i]];
		const glm::vec3& v1 = vertices[elements[i + 1]];
		const glm::vec3& v2 = vertices[elements[i + 2]];

		const glm::vec3& n0 = glm::normalize(normals[normal_elements[i]]);
		const glm::vec3& n1 = glm::normalize(normals[normal_elements[i + 1]]);
		const glm::vec3& n2 = glm::normalize(normals[normal_elements[i + 2]]);

		MeshTriangle* triangle = new MeshTriangle(v0, v1, v2, n0, n1, n2);
		objects.push_back(triangle);
	}

	AABB aabb(min, max);
	octree = Octree(aabb, objects, nullptr);
}

