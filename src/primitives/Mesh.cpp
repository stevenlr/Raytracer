#include "Raytracer.h"

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

bool Mesh::intersect(Ray ray, Hit &hit) const
{
	ray.transformInv(transform);

	Sphere sphere(glm::length(model.max - model.min) / 2, material);
	Hit hit2 = hit;
	if (!sphere.intersect(ray, hit2)) {
		return false;
	}

	float distHit = ray.tMax;
	glm::vec3 normal;
	bool reached = false;
	for (size_t i = 0; i < model.elements.size(); i += 3) {
		float dist;
		const glm::vec3& v0 = model.vertices[model.elements[i]];
		const glm::vec3& v1 = model.vertices[model.elements[i + 1]];
		const glm::vec3& v2 = model.vertices[model.elements[i + 2]];
		float alpha;
		float beta;
		if (intersectTriangle(ray, v0, v1, v2, dist, alpha, beta)
			&& dist < distHit && dist >= ray.tMin && dist <= hit.t) {
			distHit = dist;
			reached = true;

			glm::vec3 n0 = glm::normalize(model.normals[model.normal_elements[i]]);
			glm::vec3 n1 = glm::normalize(model.normals[model.normal_elements[i + 1]]);
			glm::vec3 n2 = glm::normalize(model.normals[model.normal_elements[i + 2]]);
			normal = glm::vec3(0);
			normal = (1 - alpha - beta) * n0 + alpha * n1 + beta * n2;
			normal = glm::normalize(normal);
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

