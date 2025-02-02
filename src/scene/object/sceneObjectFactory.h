#pragma once
#include "ray.h"
#include "sceneObject.h"

enum class ElementType {
  // 3D primitives
  SPHERE,
  CUBIC,
  CYLINDER,
  MODEL3D,
  CAMERA,
  // Lights
  POINT_LIGHT,
  DIRECTIONAL_LIGHT,
  SPOT_LIGHT,
  // 2D primitives
  TRIANGLE,
  CIRCLE,
  SQUARE,
  LINE,
  STAR,
  POINT,
  // 2D splines
  CATMULL_ROM_SPLINE,
  // 2D Complex shapes
  SPACE_ROCKET,
  MAGIC_SWORD,
  // 3D models
  PLANET_EARTH,
  FREDDY_PLUSH,
  SPACE_SHIP,
  NONE,
};

class SceneObjectFactory {
public:
  static std::unique_ptr<SceneObject> createDefaultSceneObject(const glm::vec3 &position, const ElementType primitiveType);
  static std::unique_ptr<SceneObject> createSceneObject(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition, const ElementType primitiveType);
};
