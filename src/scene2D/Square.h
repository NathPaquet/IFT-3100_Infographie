#pragma once
#include "ofMain.h"
#include "raycasting/ray.h"
#include "sceneObject.h"
class Square : public SceneObject {
public:
  Square(const Ray &ray, const float &distance);
  static void drawDefaultPreview(const Ray &ray, const float &distance);
};
