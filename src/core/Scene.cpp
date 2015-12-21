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

vec3 Scene::getShadeFromRay(Ray ray) const
{
    Hit hit = launchRay(ray);
    return hit.reached ? shade(ray, hit) : backgroundColor;
}

Hit Scene::launchRay(Ray ray) const
{
 	Hit hit;

	for (const Object *o : objects) {
		o->intersect(ray, hit);
	}

	return hit;
}

vec3 Scene::shade(const Ray &ray, const Hit &hit) const
{
    vec3 color(0);

    for (const Light *l : lights) {
        Ray lightRay = l->getRayFromHit(hit);

        lightRay.tMin += 0.001f;

        Hit lightHit = launchRay(lightRay);

        if (!lightHit.reached) {
            color += hit.shade(ray, l);
        }
    }

    return color;
}

void Scene::setBackgroundColor(vec3 color)
{
    backgroundColor = color;
}
