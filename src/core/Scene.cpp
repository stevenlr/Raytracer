#include "Raytracer.h"

using namespace std;
using namespace glm;

void Scene::addObject(Object *o)
{
	objects.push_back(o);
}

void Scene::addLight(Light *l)
{
	lights.push_back(l);
}

vec3 Scene::launchRay(Ray ray) const
{
 	bool reached = false;
 	Hit hit;
 	Ray rayMin(ray);

	for (const Object *o : objects) {
		if (o->intersect(ray, hit)) {
			reached = true;
			rayMin = ray;
		}
	}

	return reached ? shade(rayMin, hit) : backgroundColor;
}

vec3 Scene::shade(const Ray &ray, const Hit &hit) const
{
    vec3 color(0);

    for (const Light *l : lights) {
        color += hit.shade(ray, l);
    }

    return color;
}

void Scene::setBackgroundColor(glm::vec3 color)
{
    backgroundColor = color;
}
