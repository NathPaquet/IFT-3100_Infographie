#pragma once

#include "layouts/ColorPicker.h"
#include "ofMain.h"

class SceneObject {
public:
  ofVec3f position;
  ofColor color;

  virtual void draw() const;
  virtual void draw_properties();
  const of3dPrimitive &getPrimitive() const;

protected:
  std::unique_ptr<of3dPrimitive> primitive;
  ofMesh mainMesh;
  ofTexture mTex;
  ofImage image;
  ColorPicker colorPicker;
};
