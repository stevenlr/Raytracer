#include "Raytracer.h"

#include <glm/gtx/transform.hpp>

using namespace glm;

Transform &Transform::identity()
{
	isDirty = true;
	transform = mat4();
	return *this;
}

Transform &Transform::translate(const vec3 &v)
{
	isDirty = true;
	transform = glm::translate(transform, v);
	return *this;
}

Transform &Transform::translate(float x, float y, float z)
{
	isDirty = true;
	transform = glm::translate(transform, vec3(x, y, z));
	return *this;
}

Transform &Transform::rotate(float x, float y, float z)
{
	isDirty = true;
	transform = glm::rotate(transform, x, vec3(1, 0, 0));
	transform = glm::rotate(transform, y, vec3(0, 1, 0));
	transform = glm::rotate(transform, z, vec3(0, 0, 1));
	return *this;
}

Transform &Transform::rotate(const vec3 &axis, float angle)
{
	isDirty = true;
	transform = glm::rotate(transform, angle, axis);
	return *this;
}

Transform &Transform::scale(float scale)
{
	isDirty = true;
	transform = glm::scale(transform, vec3(scale, scale, scale));
	return *this;
}

Transform &Transform::scale(float sx, float sy, float sz)
{
	isDirty = true;
	transform = glm::scale(transform, vec3(sx, sy, sz));
	return *this;
}

Transform &Transform::scale(const vec3 &scale)
{
	isDirty = true;
	transform = glm::scale(transform, scale);
	return *this;
}

const mat4 &Transform::getTransform() const
{
	updateCache();
	return transform;
}

const mat4 &Transform::getInverseTransform() const
{
	updateCache();
	return inverse;
}

const glm::mat3 &Transform::getInverse3Transform() const
{
	updateCache();
	return inverse3;
}

const mat3 &Transform::getNormalMatrix() const
{
	updateCache();
	return normal;
}

void Transform::updateCache() const
{
	if (!isDirty) {
		return;
	}

	isDirty = false;
	inverse = glm::inverse(transform);
	inverse3 = glm::inverse(mat3(transform));
	normal = glm::inverse(glm::transpose(mat3(transform)));
}

vec3 Transform::apply(vec3 p) const
{
	updateCache();

	glm::vec4 h(p, 1);
	h = transform * h;
	return glm::vec3(h) / h.w;
}

vec3 Transform::applyInv(vec3 p) const
{
	updateCache();

	glm::vec4 h(p, 1);
	h = inverse * h;
	return glm::vec3(h) / h.w;
}
