#ifndef PRIMITIVES_PLANE_H_
#define PRIMITIVES_PLANE_H_

#include "Raytracer.h"

class Plane : public Object {
public:
	Plane(glm::vec3 pos, glm::vec3 normal, Material m) :
		Object(m),
		pos(pos), normal(normal)
	{}

	bool intersect(Ray ray, Hit &hit) const override;

	glm::vec3 pos;
	glm::vec3 normal;
};

#endif

