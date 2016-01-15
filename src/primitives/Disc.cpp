#include <limits>

#include "Raytracer.h"

using namespace std;

bool Disc::intersect(Ray ray, Hit &hit) const
{
    ray.transformInv(transform);

	float dotDir = glm::dot(ray.dir, normal);
	float dotOrig = glm::dot(ray.orig, normal);

    if (abs(dotDir) < numeric_limits<float>::epsilon()) {
        return false;
    }

	float t = -dotOrig / dotDir;

	if (t < ray.tMin || t > ray.tMax || t > hit.t) {
		return false;
	}

    if (glm::length2(ray(t)) > radius2) {
        return false;
    }

	hit.t = t;
	hit.reached = true;
	hit.material = material;
	hit.normal = normal;
    hit.pos = ray(t);
    hit.transform(transform);
	
	return true;
}