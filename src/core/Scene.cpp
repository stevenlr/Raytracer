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

	void makeBase(vec3 normal, vec3 *b1, vec3 *b2)
	{
		if (fabsf(normal.x) > fabsf(normal.y)) {
			float invLen = 1.0f / sqrtf(normal.x * normal.x + normal.z * normal.z);
			*b1 = vec3(-normal.z * invLen, 0.0f, normal.x * invLen);
		} else {
			float invLen = 1.0f / sqrtf(normal.y * normal.y + normal.z * normal.z);
			*b1 = vec3(0.0f, normal.z * invLen, -normal.y * invLen);
		}

		*b2 = glm::cross(normal, *b1);
	}

	vec3 cosineDirection(vec3 normal, float *probability)
	{
		vec3 b1, b2;
		float a = dice() * 2 * PI_F;
		float b = dice();

		makeBase(normal, &b1, &b2);
		*probability = sqrtf(1 - b) * INV_PI_F;

		return normal * sqrtf(1 - b) + sqrtf(b) * (cosf(a) * b1 + sinf(a) * b2);
	}

	float lambertBrdf(vec3 in, vec3 out, vec3 normal)
	{
		return INV_PI_F;
	}
}

vec3 Scene::doPathTracing(Ray ray) const
{
	vec3 accumulatedColor(0);
	vec3 mask(1);
	float russianRoulette = 1;
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
		Ray ambientRay(hit.pos, cosineDirection(hit.normal, &probabilityAmbient), epsilon);
		Hit ambientHit = launchRay(ambientRay);

		if (!ambientHit.reached) {
			accumulatedNow += hit.material.diffuseColor * lambertBrdf(ambientRay.dir, ray.dir, hit.normal)
				* ambientColor
				* glm::max(glm::dot(hit.normal, ambientRay.dir), 0.0f)
				/ probabilityAmbient / russianRoulette;
		}

		// lights
		for (const Light *l : lights) {
			Ray lightRay = l->getRayFromHit(hit);

			lightRay.tMin += epsilon;

			Hit lightHit = launchRay(lightRay);

			if (!lightHit.reached) {
				accumulatedNow += hit.material.diffuseColor * lambertBrdf(lightRay.dir, ray.dir, hit.normal)
					* l->getColor(hit.pos)
					* glm::max(glm::dot(hit.normal, lightRay.dir), 0.0f) / russianRoulette;
			}
		}

		// Material emission
		accumulatedNow += hit.material.diffuseColor * hit.material.emission;

		accumulatedColor += mask * accumulatedNow;

		// path
		Ray newRay = Ray(hit.pos, cosineDirection(hit.normal, &probabilityBounce), epsilon);
		
		mask *= hit.material.diffuseColor * lambertBrdf(newRay.dir, ray.dir, hit.normal)
			* glm::max(glm::dot(hit.normal, newRay.dir), 0.0f)
			/ probabilityBounce / russianRoulette;

		ray = newRay;
		bounce++;
		russianRoulette = 0.75f;
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
