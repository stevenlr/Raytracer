#include "Raytracer.h"

using namespace glm;

Ray::Ray(glm::vec3 orig, glm::vec3 dir, float tMin) : orig(orig), dir(normalize(dir)), tMin(tMin) {

}

Ray::~Ray() {

}
