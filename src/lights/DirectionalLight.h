#ifndef LIGHTS_DIRECTIONAL_LIGHT_H_
#define LIGHTS_DIRECTIONAL_LIGHT_H_

#include "Raytracer.h"

class DirectionalLight : public Light {
public:
    DirectionalLight(glm::vec3 dir, glm::vec3 color) :
           dir(glm::normalize(dir)), color(color)
    {}

    Ray getRayFromHit(const Hit &hit) const override;
    glm::vec3 getColor(glm::vec3 hitPos) const override;

    glm::vec3 dir;
    glm::vec3 color;
};

#endif