#ifndef CORE_HIT_H_
#define CORE_HIT_H_

#include "Raytracer.h"

class Hit {
public:
	Hit() = default;
	Hit(Material material, glm::vec3 normal, float t = 0) :
		material(material), normal(normal), t(t)
	{}

	Hit(const Hit &h) = default;
	Hit &operator=(const Hit &h) = default;
		
	glm::vec3 shade(const Ray &ray) const;

	bool reached;
	float t;
	Material material;
	glm::vec3 normal;
};

#endif
