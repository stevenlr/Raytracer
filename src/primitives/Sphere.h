#ifndef PRIMITIVES_SPHERE_H_
#define PRIMITIVES_SPHERE_H_

#include "Raytracer.h"

class Sphere : public Object {
	Sphere(glm::vec3 pos, float r, Material m) :
		pos(pos), radius(r), material(m), radius2(r * r);

	override bool intersect(Ray ray, Hit &hit) const;

	glm::vec3 pos;
	float radius;
	float radius2;
};

#endif
