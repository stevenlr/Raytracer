#include "Raytracer.h"

using namespace glm;
using namespace std;

Hit::Hit() :
       t(std::numeric_limits<float>::max())
{}

vec3 Hit::shade(const Ray &ray) const
{
	return material.diffuseColor;
}

void Hit::transform(const Transform &transform)
{
   pos = transform.apply(pos);
   normal = transform.getNormalMatrix() * normal;
}
