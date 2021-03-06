#include "Octree.h"

#include <limits>

using namespace std;

Octree::Octree(AABB &box, list<Object*> &objects, Octree *parent)  :
	boundingBox(box), objects(objects), parent(parent)
{
	if (objects.size() <= MIN_ENTITY)
		return;

	list<Object*> lists[8];
	AABB boundingBoxes[8];

	glm::vec3 dist = (boundingBox.pos2 - boundingBox.pos) / 2.0f;

	for (int i = 0; i < 8; ++i) {
		glm::vec3 pos(	(i % 2) * dist.x,
		                ((i / 2) % 2) * dist.y,
		                (i < 4 ? 0 : 1) * dist.z);
		pos += boundingBox.pos;

		glm::vec3 pos2(pos + dist);

		boundingBoxes[i] = AABB(pos, pos2);
	}

	unsigned int nbStayInList = 0;
	Object *o;
	AABB AABBo;

	while (objects.size() > nbStayInList) {
		int nbCollide = 0;
		int idAABBCollide = -1;

		o = objects.front();
		objects.pop_front();

		AABBo = o->getAABB();


		for (int i = 0; i < 8; ++i) {
			if (AABBo.intersect(boundingBoxes[i])) {
				idAABBCollide = i;
				++nbCollide;
				if (nbCollide > 1) {
					break;
				}
			}
		}

		if (nbCollide > 1) {
			objects.push_back(o);
			++nbStayInList;
		} else {
			lists[idAABBCollide].push_back(o);
		}
	}

	for (int i = 0; i < 8; ++i) {
		childs[i] = new Octree(boundingBoxes[i], lists[i], this);
	}
}

bool Octree::intersect(Ray ray, Hit &hit) const
{
	Hit hitTmp = hit;

	boundingBox.intersect(ray, hit);

	if (hitTmp.reached) {
		for (auto it = objects.begin(); it != objects.end(); ++it) {
			(*it)->intersect(ray, hit);
		}

		hitTmp = hit;
		if (objects.size() > MIN_ENTITY) {
			for (int i = 0; i < 8; ++i) {
				childs[i]->intersect(ray, hitTmp);
			}
		}

		if (hitTmp.reached && hit.t > hitTmp.t) {
			hit = hitTmp;
		}
	} else {
		hit.reached = false;
	}

	return hit.reached;
}
