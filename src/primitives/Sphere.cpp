#include "Raytracer.h"

Sphere::Sphere(float r, Material m) :
		Object(m),
		radius(r), radius2(r * r)
{
	aabb.pos = glm::vec3(-radius);
	aabb.pos2 = glm::vec3(radius);
}

bool Sphere::intersect(Ray ray, Hit &hit) const
{
    ray.transformInv(transform);

	float tproj = glm::dot(ray.dir, -ray.orig);

	glm::vec3 projPoint = ray(tproj);
	glm::vec3 minPoint = ray(ray.tMin);
    glm::vec3 maxPoint = ray(ray.tMax);
	float dist2Proj = glm::length2(projPoint);
	float dist2Min = glm::length2(minPoint);
    float dist2Max = glm::length2(maxPoint);

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