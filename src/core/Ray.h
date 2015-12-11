#ifndef CORE_RAY_H
#define CORE_RAY_H

#include <glm/glm.hpp>

class Ray {
public:
	Ray(glm::vec3 orig, glm::vec3 dir, float tMin);
	Ray(const Ray & ray) = default;

	glm::vec3 operator()(float t) const {
		return orig + dir * t;
	}

	Ray &operator=(const Ray & ray) = default;

	float tMin;
	glm::vec3 orig;
	glm::vec3 dir;
};

#endif
