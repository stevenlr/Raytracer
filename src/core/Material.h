#ifndef CORE_MATERIAL_H_
#define CORE_MATERIAL_H_

#include <glm/glm.hpp>

class Material
{
public:
	Material() = default;
	Material(glm::vec3 diffuseColor, float metaliness = 0, float roughness = 1, float emission = 0) :
		diffuseColor(diffuseColor), emission(emission), metaliness(metaliness)
	{
		exponent = glm::pow(8192, 1 - roughness);
	}

	Material(const Material &m) = default;
	Material &operator=(const Material &m) = default;

	float brdf(glm::vec3 in, glm::vec3 out, glm::vec3 normal);
	glm::vec3 sample(glm::vec3 in, glm::vec3 normal, float *probability);

	glm::vec3 diffuseColor;
	float emission;
	float metaliness;
	float exponent;
};

#endif
