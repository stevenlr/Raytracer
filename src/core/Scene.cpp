#include <iostream>

#include "Scene.h"

using namespace std;

void Scene::addObject(Object *o) {
	objects.push_back(o);
}

glm::vec3 Scene::launchRay(Ray ray) {
 	bool reached = false;
 	Hit hit;
 	Ray rayLocalMin(ray);

	for (list<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		Object *o = *it;

		Ray rayLocal = ray;
		rayLocal.transform(o->transform);

		if (o->intersect(rayLocal, hit)) {
			reached = true;
			rayLocalMin = rayLocal;
		}
	}

	return reached ? hit.shade(rayLocalMin) : glm::vec3(0);
}
