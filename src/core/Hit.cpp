#include "Raytracer.h"

using namespace glm;

vec3 Hit::shade(const Ray &ray) const
{
	return material.diffuseColor;
}
