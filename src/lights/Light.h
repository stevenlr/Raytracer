#ifndef LIGHTS_LIGHT_H_
#define LIGHTS_LIGHT_H_

#include "Raytracer.h"

class Light {
public:
    virtual ~Light() {}
    virtual Ray getRayFromHit(const Hit &hit) const = 0;
    virtual glm::vec3 getColor(glm::vec3 hitPos) const = 0;
};

#endif
