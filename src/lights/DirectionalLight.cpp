#include "Raytracer.h"

using namespace glm;
using namespace std;

Ray DirectionalLight::getRayFromHit(const Hit &hit) const
{
	return Ray(hit.pos, -dir, 0, numeric_limits<float>::max());
}

glm::vec3 DirectionalLight::getColor(glm::vec3 hitPos) const
{
	return color;
}
