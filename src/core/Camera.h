#ifndef CORE_CAMERA_H
#define CORE_CAMERA_H

#include "Raytracer.h"

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, int width, int height, float near, float far);

	Ray computeRay(float x, float y);

	int width;
	int height;

private:
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 invViewProjection;
};

#endif
