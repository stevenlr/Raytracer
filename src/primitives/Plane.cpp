#include <limits>

#include "Raytracer.h"

#include <iostream>


using namespace std;

bool Plane::intersect(Ray ray, Hit &hit) const
{
	float dotDir = glm::dot(ray.dir, normal);
	float dotOrig = glm::dot(ray.orig, normal);

    if (abs(dotDir) < numeric_limits<float>::epsilon()) {
        return false;
    }

	float t = -dotOrig / dotDir;

	if (t < ray.tMin || t > hit.t) {
		return false;
	}

	hit.t = t;
	hit.reached = true;
	hit.material = material;
	hit.normal = normal;
	
	return true;
}
