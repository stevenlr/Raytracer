#include "Raytracer.h"

using namespace glm;

Ray::Ray(glm::vec3 orig, glm::vec3 dir, float tMin) :
		orig(orig), dir(normalize(dir)), tMin(tMin)
{}

void Ray::transform(const Transform &t)
{
	vec4 o(orig, 1);

	o = t.getInverseTransform() * o;
	orig = glm::vec3(o) / o.w;
	dir = glm::mat3(t.getInverseTransform()) * dir;

	float newLength = glm::length(dir);
	tMin /= newLength;
	dir /= newLength;
}
