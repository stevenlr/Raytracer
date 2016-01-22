#include "Raytracer.h"

#include <random>
#include <functional>
#include <iostream>

using namespace std;
using namespace glm;

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

	vec3 blinnDirection(vec3 normal, float *probability, float exponent)
	{
		vec3 b1, b2;
		float a = dice() * 2 * PI_F;
		float b = dice();

		float cosTheta = powf(b, 1 / (exponent + 1));
		float sinTheta = sqrtf(1 - cosTheta * cosTheta);

		makeBase(normal, &b1, &b2);
		*probability = (exponent + 1) / 2 * INV_PI_F * glm::pow(cosTheta, exponent);

		return cosTheta * normal + sinTheta * (cosf(a) * b1 + sinf(a) * b2);
	}
}

float Material::brdf(vec3 in, vec3 out, vec3 normal)
{
	float lambert = INV_PI_F;
	vec3 half = glm::normalize(in + out);
	float blinnPhong = (exponent + 1) / 2 * INV_PI_F * glm::pow(glm::max(glm::dot(normal, half), 0.0f), exponent);

	return metaliness * blinnPhong + (1 - metaliness) * lambert;
}

vec3 Material::sample(vec3 in, vec3 normal, float *probability) 
{
	float n = dice();
	vec3 dir;

	if (n < metaliness) {
		vec3 half = blinnDirection(normal, probability, exponent);
		dir = glm::normalize(2 * glm::dot(in, half) * half - in);

		if (glm::dot(dir, normal) < 0) {
			dir = glm::normalize(dir - 2 * glm::dot(dir, normal) * normal);
		}

		*probability *= metaliness;
	} else {
		dir = cosineDirection(normal, probability);
		*probability *= 1 - metaliness;
	}

	return dir;
}