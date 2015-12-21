#include "Raytracer.h"

bool Sphere::intersect(Ray ray, Hit &hit) const
{
    ray.transformInv(transform);

	float tproj = glm::dot(ray.dir, -ray.orig);

	glm::vec3 projPoint = ray(tproj);
	glm::vec3 minPoint = ray(ray.tMin);
	float dist2Proj = glm::length2(projPoint);
	float dist2Min = glm::length2(minPoint);

	if ((dist2Min > radius2 && tproj < ray.tMin) || dist2Proj > radius2) {
		return false;
	}

	float dt = sqrt(radius2 - dist2Proj);
	float t;
	
	if (dist2Min > radius2) {
		t = tproj - dt;
	} else {
		t = tproj + dt;
	}

	if (t < ray.tMin || t > ray.tMax || t > hit.t) {
		return false;
	}

	hit.t = t;
	hit.reached = true;
	hit.material = material;
    hit.pos = ray(t);
    hit.normal = glm::normalize(hit.pos);
    hit.transform(transform);

	return true;
}
