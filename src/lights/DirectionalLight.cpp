#include "Raytracer.h"

using namespace glm;

Ray DirectionalLight::getRayFromHit(const Hit &hit) const
{
    return Ray(hit.pos, -dir, 0);
}

glm::vec3 DirectionalLight::getColor(glm::vec3 hitPos) const
{
    return color;
}
