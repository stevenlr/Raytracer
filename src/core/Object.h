#ifndef CORE_OBJECT_H_
#define CORE_OBJECT_H_

#include "Raytracer.h"

class Object {
public:
	Object(Material material) :
		material(material)
	{}

	virtual ~Object() {}

	virtual bool intersect(Ray ray, Hit &hit) = 0 const;

	Material material;
};

#endif
