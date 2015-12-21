#include "Raytracer.h"

using namespace glm;

Ray PointLight::getRayFromHit(const Hit &hit) const
{
    return Ray(hit.pos, glm::normalize(pos - hit.pos), 0);
}

glm::vec3 PointLight::getColor(glm::vec3 hitPos) const
{
    float dist = glm::length(pos - hitPos);
    glm::vec3 polynomialDist(1, dist, dist * dist);

    return color / glm::dot(polynomialDist, attenuation);
}
