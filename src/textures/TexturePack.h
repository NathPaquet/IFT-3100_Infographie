#pragma once
#include "ofMain.h"

#include <string>

class TexturePack {
public:
  TexturePack() = default;
  TexturePack(const ofImage &image, const std::string &id);
  TexturePack(const std::string &packName);

  void loadSingleImage(const ofImage &image, const std::string &id);

  bool load(const std::string &packName);
  void configureTexture(ofTexture &texture);
  void configureMaterial(std::shared_ptr<ofShader> shader);
  void setMetallicity(float metallicity);
  void setDisplacementStrength(float displacementStrength);
  void setRoughness(float roughness);
  float getMetallicity() const;
  float getRoughness() const;
  float getDisplacementStrength() const;

  // diffuse texture map holds the color information
  ofTexture textureDiffuseMap;
  // texture holding the normal values for the mesh that will be used for lighting in the frag shader
  ofTexture textureNormalMap;
  // texture holding the values for how far to offset the mesh vertices in vertex shader
  ofTexture textureDisplacementMap;
  // texture holding ambient occlusion, roughness and metal properties
  // we will only be using the ambient occlusion value stored in the red channel
  ofTexture textureAORoughMetal;

  ofMaterial material;

  ofFloatColor baseColor;

  std::string packId;
  ofPixels defaultPixels;

  float metallic = 0.5f;
  float roughness = 0.5f;
  float displacementStrength = 0.5f;
};