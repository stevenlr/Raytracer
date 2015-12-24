#include "Raytracer.h"

using namespace glm;

Ray::Ray(glm::vec3 orig, glm::vec3 dir, float tMin, float tMax) :
		orig(orig), dir(normalize(dir)), tMin(tMin), tMax(tMax)
{}

void Ray::transformInv(const Transform &t)
{
    orig = t.applyInv(orig);
	dir = glm::normalize(t.getInverse3Transform() * dir);
}
