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
	return aabb.pos.x 			<= pos2.x - 1
	       and aabb.pos2.x - 1		>= pos.x
	       and aabb.pos.y			<= pos2.y - 1
	       and aabb.pos2.y - 1		>= pos.y
	       and aabb.pos.z			<= pos2.z - 1
	       and aabb.pos2.z - 1		>= pos.z;
	/*todo Replace box2 by pos2, box by pos + add z coord
	return	box2.x				<= box1.x + box1.w -1
		and box2.x + box2.w -1	>= box1.x
		and box2.y 				<= box1.y + box1.h -1
		and box2.y + box2.h -1	>= box1.y;*/
}