#ifndef PRIMITIVES_OCTREE_H_
#define PRIMITIVES_OCTREE_H_

#include "Raytracer.h"

#include <list>

#define MAX_SIZE 1
#define MIN_ENTITY 1

class Octree
{
public:
	Octree(AABB &box, std::list<Object*> &objects, Octree *parent);

	Octree *parent;
	Octree *childs[8];

	AABB boundingBox;
	std::list<Object*> objects;

	bool intersect(Ray ray, Hit &hit) const;

};

#endif
