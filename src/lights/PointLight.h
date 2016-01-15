#ifndef LIGHTS_POINT_LIGHT_H_
#define LIGHTS_POINT_LIGHT_H_

#include "Raytracer.h"

class PointLight : public Light
{
public:
	PointLight(glm::vec3 pos, glm::vec3 color, glm::vec3 attenuation) :
		pos(pos), color(color), attenuation(attenuation)
	{}

	Ray getRayFromHit(const Hit &hit) const override;
	glm::vec3 getColor(glm::vec3 hitPos) const override;

	glm::vec3 pos;
	glm::vec3 color;
	glm::vec3 attenuation;
};

#endif
