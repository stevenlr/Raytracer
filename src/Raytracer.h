#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

class Material;
class Hit;
class AABB;
class Object;
class Camera;
class Scene;
class Octree;
class Ray;
class Transform;
class Plane;
class Disc;
class Sphere;
class Light;
class DirectionalLight;
class PointLight;

#define PI_F 3.14159265359f

#include "core/Material.h"
#include "core/Hit.h"
#include "core/Transform.h"
#include "core/AABB.h"
#include "core/Object.h"
#include "core/Camera.h"
#include "core/Scene.h"
#include "core/Ray.h"
#include "core/Octree.h"

#include "primitives/Sphere.h"
#include "primitives/Plane.h"
#include "primitives/Disc.h"

#include "lights/Light.h"
#include "lights/DirectionalLight.h"
#include "lights/PointLight.h"

#endif
