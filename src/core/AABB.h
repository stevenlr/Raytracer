#ifndef PRIMITIVES_AABB_H_
#define PRIMITIVES_AABB_H_

#include "Raytracer.h"

class AABB
{
public:
	AABB() = default;
	AABB(glm::vec3 &pos, glm::vec3 &pos2) :
		pos(pos), pos2(pos2)
	{}

	bool intersect(Ray ray, Hit &hit) const;
	bool intersect(AABB aabb) const;

	glm::vec3 pos, pos2;
};

#endif
