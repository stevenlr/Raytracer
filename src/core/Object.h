#ifndef CORE_OBJECT_H_
#define CORE_OBJECT_H_

#include "Raytracer.h"

class Object {
public:
	Object(Material material) :
		material(material)
	{}

	virtual ~Object() {}

	virtual bool intersect(Ray ray, Hit &hit) const = 0;

	AABB getAABB() const
	{
		if (!computed) {
			computed = true;

			glm::vec3 pos[8];
			glm::vec3 whd = aabb.pos2 - aabb.pos;

			for (int i = 0; i < 8; ++i) {
				pos[i] = glm::vec3(	(i % 2),
									((i / 2) % 2),
									(i < 4 ? 0 : 1));
				pos[i] = pos[i] * whd + aabb.pos;
				pos[i] = transform.apply(pos[i]);
			}

			for (int i = 0; i < 8; ++i) {
				aabb.pos = glm::min(aabb.pos, pos[i]);
				aabb.pos2 = glm::max(aabb.pos2, pos[i]);
			}
		}
		
		return aabb;
	}

	Material material;
	Transform transform;

protected:
	mutable bool computed;
	mutable AABB aabb;
};

#endif
