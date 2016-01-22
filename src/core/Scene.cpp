#include "Raytracer.h"

#include <iostream>
#include <random>
#include <functional>

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

namespace
{
	static default_random_engine generator;
	static uniform_real_distribution<float> rand(0, 1);
	static auto dice = bind(rand, generator);
}

vec3 Scene::doPathTracing(Ray ray) const
{
	vec3 accumulatedColor(0);
	vec3 mask(1);
	const float russianRoulette = 0.75f;
	int bounce = 0;
	const float epsilon = numeric_limits<float>::epsilon() * 100;
	float probabilityBounce = 1;

	do {
		Hit hit = launchRay(ray);
		vec3 accumulatedNow(0);

		if (!hit.reached) {
			return (bounce == 0) ? ambientColor : vec3(0);
		}

		// ambient
		float probabilityAmbient;
		Ray ambientRay(hit.pos, hit.material.sample(-ray.dir, hit.normal, &probabilityAmbient), epsilon);
		Hit ambientHit = launchRay(ambientRay);

		if (!ambientHit.reached) {
			accumulatedNow += hit.material.diffuseColor * hit.material.brdf(ambientRay.dir, -ray.dir, hit.normal)
				* ambientColor
				* glm::max(glm::dot(hit.normal, ambientRay.dir), 0.0f)
				/ probabilityAmbient;
		}

		// lights
		for (const Light *l : lights) {
			Ray lightRay = l->getRayFromHit(hit);

			lightRay.tMin += epsilon;

			Hit lightHit = launchRay(lightRay);

			if (!lightHit.reached) {
				accumulatedNow += hit.material.diffuseColor * hit.material.brdf(lightRay.dir, -ray.dir, hit.normal)
					* l->getColor(hit.pos)
					* glm::max(glm::dot(hit.normal, lightRay.dir), 0.0f);
			}
		}

		// Material emission
		accumulatedNow += hit.material.diffuseColor * hit.material.emission;

		accumulatedColor += mask * accumulatedNow;

		// Sooooooo... no dividing by russian roulette probabiility? :o

		// path
		Ray newRay = Ray(hit.pos, hit.material.sample(-ray.dir, hit.normal, &probabilityBounce), epsilon);
		
		mask *= hit.material.diffuseColor * hit.material.brdf(newRay.dir, -ray.dir, hit.normal) * glm::max(glm::dot(hit.normal, newRay.dir), 0.0f) / probabilityBounce;
		ray = newRay;
		bounce++;
	} while (dice() < russianRoulette);

	return accumulatedColor;
}

Hit Scene::launchRay(Ray ray) const
{
	Hit hit;

	for (const Object *o : objects) {
		o->intersect(ray, hit);
	}

	return hit;
}

void Scene::setAmbientColor(vec3 color)
{
	ambientColor = color;
}
