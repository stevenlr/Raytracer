#include "Raytracer.h"

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

namespace {
    static default_random_engine generator;
    static uniform_real_distribution<float> rand(0, 1);
    static auto dice = bind(rand, generator);

    vec3 cosineDirection(vec3 normal)
    {
        vec3 b1, b2;

        if (fabsf(normal.x) > fabsf(normal.y)) {
            float invLen = 1.0f / sqrtf(normal.x * normal.x + normal.z * normal.z);
            b1 = vec3(-normal.z * invLen, 0.0f, normal.x * invLen);
        } else {
            float invLen = 1.0f / sqrtf(normal.y * normal.y + normal.z * normal.z);
            b1 = vec3(0.0f, normal.z * invLen, -normal.y * invLen);
        }

        b2 = glm::cross(normal, b1);

        float a = dice() * 2 * PI_F;
        float b = dice();

        return normal * sqrt(1 - b) + sqrt(b) * (cos(a) * b1 + sin(a) * b2);
    }
}

vec3 Scene::doPathTracing(Ray ray) const
{
    vec3 accumulatedColor(0);
    vec3 mask(1);
    const float russianRoulette = 0.75f;
    int bounce = 0;
    const float epsilon = numeric_limits<float>::epsilon() * 100;

    do {
        Hit hit = launchRay(ray);

        if (!hit.reached) {
            return (bounce == 0) ? ambientColor : vec3(0);
        }

        mask *= hit.material.diffuseColor;

        // ambient
        Ray ambientRay(hit.pos, cosineDirection(hit.normal), epsilon);
        Hit ambientHit = launchRay(ambientRay);

        if (!ambientHit.reached) {
            accumulatedColor += ambientColor * mask;
        }

        // lights
        for (const Light *l : lights) {
            Ray lightRay = l->getRayFromHit(hit);

            lightRay.tMin += epsilon;

            Hit lightHit = launchRay(lightRay);

            if (!lightHit.reached) {
                accumulatedColor += l->getColor(hit.pos) * max(glm::dot(hit.normal, lightRay.dir), 0.0f) * mask;
            }
        }

        // path
        ray = Ray(hit.pos, cosineDirection(hit.normal), epsilon);
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
