#include "Raytracer.h"

using namespace glm;

Ray::Ray(glm::vec3 orig, glm::vec3 dir, float tMin) :
		orig(orig), dir(normalize(dir)), tMin(tMin)
{}

void Ray::transform(const Transform &t)
{
    orig = t.applyInv(orig);
	dir = glm::mat3(t.getInverseTransform()) * dir;

	float newLength = glm::length(dir);
	tMin /= newLength;
	dir /= newLength;
}
