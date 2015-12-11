#include "Raytracer.h"

bool Sphere::intersect(Ray ray, Hit &hit) const
{
	float tproj = glm::dot(ray.dir, pos - ray.orig);

	glm::vec3 projPoint = ray(tproj);
	glm::vec3 minPoint = ray(ray.tMin);
	float dist2Proj = length2(projPoint - pos);
	float dist2Min = length2(minPoint - pos);

	if ((dist2Min > radius2 && tproj < ray.tMin) || dist2Proj > radius2) {
		hit.reached = false;
		return false;
	}

	float dt = sqrt(radius2 - dist2Proj);

	hit.reached = true;

	if (dist2Min > radius2) {
		hit.t = tproj + dt;
	} else {
		hit.t = tproj - dt;
	}

	return true;
}
