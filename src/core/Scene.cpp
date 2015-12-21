#include <iostream>

#include "Scene.h"

using namespace std;

void Scene::addObject(Object *o)
{
	objects.push_back(o);
}

void Scene::addLight(Light *l)
{
	lights.push_back(l);
}

glm::vec3 Scene::launchRay(Ray ray)
{
 	bool reached = false;
 	Hit hit;
 	Ray rayMin(ray);

	for (list<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		Object *o = *it;

		if (o->intersect(ray, hit)) {
			reached = true;
			rayMin = ray;
		}
	}

	return reached ? hit.shade(rayMin) : glm::vec3(0);
}
