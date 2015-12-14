#ifndef PRIMITIVES_AABB_H_
#define PRIMITIVES_AABB_H_

#include "Raytracer.h"

class AABB {
public:
	AABB(glm::vec3 &pos, glm::vec3 &pos2) :
		pos(pos), pos2(r)
	{}

	bool intersect(Ray ray, Hit &hit) const override;

	glm::vec3 pos, pos2;
};

#endif
