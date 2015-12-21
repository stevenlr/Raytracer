#ifndef CORE_SCENE_H
#define CORE_SCENE_H

#include <list>
#include "Raytracer.h"

class Scene {
public:
	void addObject(Object *o);
    void addLight(Light *l);
	glm::vec3 launchRay(Ray ray) const;
    glm::vec3 shade(const Ray &ray, const Hit &hit) const;
    void setBackgroundColor(glm::vec3 color);

private:
	std::list<Object *> objects;
    std::list<Light *> lights;
    glm::vec3 backgroundColor;
};

#endif
