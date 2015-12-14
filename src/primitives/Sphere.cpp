#include "Raytracer.h"

bool Sphere::intersect(Ray ray, Hit &hit) const
{
	float tproj = glm::dot(ray.dir, -ray.orig);

	glm::vec3 projPoint = ray(tproj);
	glm::vec3 minPoint = ray(ray.tMin);
	float dist2Proj = length2(projPoint);
	float dist2Min = length2(minPoint);

	if ((dist2Min > radius2 && tproj < ray.tMin) || dist2Proj > radius2) {
		hit.reached = false;
		return false;
	}

	float dt = sqrt(radius2 - dist2Proj);
	float t;
	
	if (dist2Min > radius2) {
		t = tproj - dt;
	} else {
		t = tproj + dt;
	}

	if (t < ray.tMin || t > hit.t) {
		hit.reached = false;
		return false;
	}

	hit.t = t;
	hit.reached = true;
	hit.material = material;

	return true;
}
