#include "Raytracer.h"

static bool intersectTriangle(const Ray& ray, const glm::vec3& v0, const glm::vec3& v1,
					   const glm::vec3& v2, float& distHit)
{
	glm::mat3 M(v1 - v0, v2 - v0, -ray.dir);
	if (glm::determinant(M) == 0)
		return false;

	glm::vec3 b = glm::vec3(ray.orig) - v0;
	glm::vec3 r = glm::inverse(M) * b;
	if (r[0] >= 0 && r[1] >= 0 && r[0] + r[1] <= 1) {
		distHit = r[2];
		return true;
	}

	return false;
}

bool Mesh::intersect(Ray ray, Hit &hit) const
{
	ray.transformInv(transform);

	float distHit = ray.tMax;
	glm::vec3 normal;
	bool reached = false;
	for (size_t i = 0; i < model.elements.size(); i += 3) {
		float dist;
		const glm::vec3& v0 = model.vertices[model.elements[i]];
		const glm::vec3& v1 = model.vertices[model.elements[i + 1]];
		const glm::vec3& v2 = model.vertices[model.elements[i + 2]];
		if (intersectTriangle(ray, v0, v1, v2, dist) && dist < distHit && dist >= ray.tMin) {
			distHit = dist;
			reached = true;
			normal = model.normals[model.elements[i]];
		}
	}

	if (reached) {
		float t = distHit;
		hit.t = t;
		hit.reached = true;
		hit.material = material;
		hit.pos = ray(t);
		hit.normal = normal;
		hit.transform(transform);
	}

	return reached;
}

