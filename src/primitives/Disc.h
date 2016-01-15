#ifndef PRIMITIVES_DISC_H_
#define PRIMITIVES_DISC_H_

#include "Raytracer.h"

class Disc : public Object
{
public:
	Disc(glm::vec3 normal, float radius, Material m) :
		Object(m),
		normal(normal),
		radius2(radius * radius)
	{}

	bool intersect(Ray ray, Hit &hit) const override;

	float radius2;
	glm::vec3 normal;
};

#endif

