#ifndef PRIMITIVES_MESH_H_
#define PRIMITIVES_MESH_H_

#include "Raytracer.h"

class Mesh : public Object
{
public:
	Mesh(const MeshModel& model, Material m) :
		Object(m),
		model(model)
	{}

	bool intersect(Ray ray, Hit &hit) const override;

	const MeshModel& model;
};

#endif
