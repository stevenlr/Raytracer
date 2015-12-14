#include <iostream>

#include "Scene.h"

using namespace std;

void Scene::addObject(Object *o) {
	objects.push_back(o);
}

glm::vec3 Scene::launchRay(Ray ray) {
 	bool reached = false;
 	Hit hit;

	for (list<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		if ((*it)->intersect(ray, hit)) {
			reached = true;
		}
	}

	return reached ? hit.shade(ray) : glm::vec3(1);
}
