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
class Mesh;
class MeshModel;
class Light;
class DirectionalLight;
class PointLight;

#include "core/Material.h"
#include "core/Hit.h"
#include "core/Transform.h"
#include "core/Object.h"
#include "core/Camera.h"
#include "core/Scene.h"
#include "core/Ray.h"
#include "core/MeshModel.h"

#include "primitives/Sphere.h"
#include "primitives/Plane.h"
#include "primitives/Mesh.h"

#include "lights/Light.h"
#include "lights/DirectionalLight.h"
#include "lights/PointLight.h"

#endif
