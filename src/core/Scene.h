#ifndef CORE_SCENE_H
#define CORE_SCENE_H

#include <list>
#include "Raytracer.h"

class Scene {
public:
	void addObject(Object *o);
	glm::vec3 launchRay(Ray ray);

private:
	std::list<Object *> objects;
};

#endif
