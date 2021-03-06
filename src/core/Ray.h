#ifndef CORE_RAY_H
#define CORE_RAY_H

#include "Raytracer.h"

#include <glm/glm.hpp>

class Ray
{
public:
	Ray(glm::vec3 orig, glm::vec3 dir, float tMin = 0, float tMax = std::numeric_limits<float>::max());
	Ray(const Ray & ray) = default;

	glm::vec3 operator()(float t) const
	{
		return orig + dir * t;
	}

	Ray &operator=(const Ray & ray) = default;

	void transformInv(const Transform &t);

	float tMin;
	float tMax;
	glm::vec3 orig;
	glm::vec3 dir;
};

#endif
