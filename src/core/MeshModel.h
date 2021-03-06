#ifndef CORE_MESHMODEL_H
#define CORE_MESHMODEL_H

#include "Raytracer.h"

#include <string>
#include <vector>
#include <glm/glm.hpp>

class MeshModel
{
public:
	MeshModel(const std::string& filename);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> elements;
	std::vector<unsigned int> normal_elements;
	glm::vec3 min;
	glm::vec3 max;
};

#endif
