#ifndef PRIMITIVES_OCTREE_H_
#define PRIMITIVES_OCTREE_H_

#include "Raytracer.h"

#define MAX_SIZE 1
#define MIN_ENTITY 1

class Octree : public Object {
public:
	Octree(AABB &box, list<Object*> &objects, Octree *parent);

	Octree *parent;
	Octree *childs[8];

	AABB boundingBox;
	list<Object*> objects;

};

#endif
