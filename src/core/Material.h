#ifndef CORE_MATERIAL_H_
#define CORE_MATERIAL_H_

#include <glm/glm.hpp>

class Material
{
public:
	Material() = default;
	Material(glm::vec3 diffuseColor, float emission = 0) :
		diffuseColor(diffuseColor), emission(emission)
	{}

	Material(const Material &m) = default;
	Material &operator=(const Material &m) = default;

	glm::vec3 diffuseColor;
	float emission = 0;
};

#endif
