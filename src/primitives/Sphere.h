#ifndef PRIMITIVES_SPHERE_H_
#define PRIMITIVES_SPHERE_H_

#include "Raytracer.h"

class Sphere : public Object {
public:
	Sphere(glm::vec3 pos, float r, Material m) :
		Object(m),
		pos(pos), radius(r), radius2(r * r)
	{}

	bool intersect(Ray ray, Hit &hit) const override;

	glm::vec3 pos;
	float radius;
	float radius2;
};

#endif
