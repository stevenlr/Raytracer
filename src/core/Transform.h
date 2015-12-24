#ifndef CORE_TRANSFORM_H_
#define CORE_TRANSFORM_H_

#include <glm/glm.hpp>

class Transform {
public:
	Transform() = default;
	Transform(const Transform &t) = default;
	Transform &operator=(const Transform &t) = default;

	Transform &identity();

	Transform &translate(const glm::vec3 &v);
	Transform &translate(float x, float y, float z);

	Transform &rotate(float x, float y, float z);
	Transform &rotate(const glm::vec3 &axis, float angle);

	Transform &scale(float scale);
	Transform &scale(float sx, float sy, float sz);
	Transform &scale(const glm::vec3 &scale);

	const glm::mat4 &getTransform() const;
	const glm::mat4 &getInverseTransform() const;
    const glm::mat3 &getInverse3Transform() const;
	const glm::mat3 &getNormalMatrix() const;

    glm::vec3 apply(glm::vec3 p) const;
    glm::vec3 applyInv(glm::vec3 p) const;

private:
	void updateCache() const;

	mutable bool isDirty = false;
	glm::mat4 transform;
	mutable glm::mat4 inverse;
    mutable glm::mat3 inverse3;
	mutable glm::mat3 normal;
};

#endif
