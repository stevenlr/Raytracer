#ifndef PRIMITIVES_PLANE_H_
#define PRIMITIVES_PLANE_H_

#include "Raytracer.h"

class Plane : public Object {
public:
	Plane(glm::vec3 normal, Material m) :
		Object(m),
		normal(normal)
	{}

	bool intersect(Ray ray, Hit &hit) const override;

	glm::vec3 normal;
};

#endif

