#include "Raytracer.h"

using namespace glm;

Ray PointLight::getRayFromHit(const Hit &hit) const
{
    vec3 diff = pos - hit.pos;
    float len = glm::length(diff);

    return Ray(hit.pos, diff / len, 0, len);
}

glm::vec3 PointLight::getColor(glm::vec3 hitPos) const
{
    float dist = glm::length(pos - hitPos);
    glm::vec3 polynomialDist(1, dist, dist * dist);

    return color / glm::dot(polynomialDist, attenuation);
}
