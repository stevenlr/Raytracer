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

	float min = glm::min(far);

	hit.reached = glm::max(near) < min && tMin < min;

	return hit.reached;
}
