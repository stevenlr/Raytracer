#ifndef CORE_MATERIAL_H_
#define CORE_MATERIAL_H_

#include <glm/glm.h>

class Material {
public:
	Material(glm::vec3 diffuseColor) :
		diffuseColor(diffuseColor)
	{}

	Material(const Material &m) = default;
	Material &operator=(const Material &m) = default;

	glm::vec3 diffuseColor;
};

#endif
