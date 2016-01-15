#include "Raytracer.h"

#include <iostream>

using namespace glm;
using namespace std;

Hit::Hit() :
       t(std::numeric_limits<float>::max())
{}

vec3 Hit::shade(const Ray &ray, const Light *light) const
{
    Ray lightRay = light->getRayFromHit(*this);

    glm::vec3 lightColor = light->getColor(pos);
    float lambertFactor = glm::max(glm::dot(lightRay.dir, normal), 0.f);

	return material.diffuseColor * lightColor * lambertFactor;
}

void Hit::transform(const Transform &transform)
{
   pos = transform.apply(pos);
   normal = transform.getNormalMatrix() * normal;
}
