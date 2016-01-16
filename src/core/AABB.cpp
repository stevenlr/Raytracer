#include "Raytracer.h"

bool AABB::intersect(Ray ray, Hit &hit) const
{
	glm::vec3 near, far;

	for (int i = 0; i < 3; ++i) {
		float dist = pos[i] - ray.orig[i];
		float dist2 = pos2[i] - ray.orig[i];

		if (dist < dist2) {
			near[i] = pos[i];
			far[i] = pos2[i];
		} else {
			near[i] = pos2[i];
			far[i] = pos[i];
		}
	}

	float min = glm::min(far.x, glm::min(far.y, far.z));

	hit.reached = glm::max(near.x, glm::max(near.y, near.z)) < min && ray.tMin < min;

	return hit.reached;
}

bool AABB::intersect(AABB aabb) const
{
	return    aabb.pos.x 			<= pos2.x - 1
	       && aabb.pos2.x - 1		>= pos.x
	       && aabb.pos.y			<= pos2.y - 1
	       && aabb.pos2.y - 1		>= pos.y
	       && aabb.pos.z			<= pos2.z - 1
	       && aabb.pos2.z - 1		>= pos.z;
}
