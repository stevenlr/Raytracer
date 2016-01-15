#ifndef PRIMITIVES_SPHERE_H_
#define PRIMITIVES_SPHERE_H_

#include "Raytracer.h"

class Sphere : public Object {
public:
	Sphere(float r, Material m);

	bool intersect(Ray ray, Hit &hit) const override;

	float radius;
	float radius2;
};

#endif
