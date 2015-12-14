#include "core/Camera.h"

#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, int width, int height, float near, float far) :
		height(height), width(width) {
	view = glm::lookAt(position, target, up);
	projection = glm::perspectiveFov(fov, static_cast<float>(width), static_cast<float>(height), near, far);
	invViewProjection = glm::inverse(projection * view);
}

Ray Camera::computeRay(int x, int y) {
	glm::vec4 nearPos(static_cast<float>(x) / (width - 1) * 2 - 1,
		(height - static_cast<float>(y) - 1) / (height - 1) * 2 - 1, -1, 1);
	glm::vec4 farPos(nearPos.x, nearPos.y, 1, 1);

	nearPos = invViewProjection * nearPos;
	farPos = invViewProjection * farPos;

	return Ray(glm::vec3(nearPos / nearPos.w),
		glm::normalize(glm::vec3(farPos / farPos.w - nearPos / nearPos.w)), 0);
}