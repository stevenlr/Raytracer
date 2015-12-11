#include "Scene.h"

void Scene::addObject(Object *o) {
	objects.push_back(o);
}

glm::vec3 Scene::launchRay(Ray ray) {
 	Hit hit;

	for (list<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		if (it->intersect(ray, &hit)) {
			ray.tMin = hit.t;
		}
	}

	return hit.shade(ray);
}
