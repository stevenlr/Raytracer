#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

class Material;
class Hit;
class Object;
class Camera;
class Scene;
class Ray;
class Transform;
class Plane;
class Sphere;
class Light;
class DirectionalLight;

#include "core/Material.h"
#include "core/Hit.h"
#include "core/Transform.h"
#include "core/Object.h"
#include "core/Camera.h"
#include "core/Scene.h"
#include "core/Ray.h"

#include "primitives/Sphere.h"
#include "primitives/Plane.h"

#include "lights/Light.h"
#include "lights/DirectionalLight.h"

#endif
