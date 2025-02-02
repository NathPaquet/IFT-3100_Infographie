#pragma once
#include "TexturePack.h"

#include <memory>
#include <vector>

class TextureRepository {
public:
  friend class TextureEditor;
  static void addTexture(const std::string &packName);
  static void addTextureFromSingleImage(const ofImage &image, const std::string &id);
  static const std::list<std::unique_ptr<TexturePack>> &getTextures();
  static void configureTextureWithShader(const std::string &id, std::shared_ptr<ofShader> shader);
  static const TexturePack *getTexture(const std::string &packId);

private:
  static void setDisplacementMap(const std::string &id, const ofTexture &texture);
  static void setTextureDiffuseMap(std::function<void(ofTexture &)> callback, const std::string &id);
  static void setMetallicity(const std::string &id, float metallicity);
  static void setRoughness(const std::string &id, float roughness);
  static void setBrightness(const std::string &id, float brightness);
  static void setDisplacementStrength(const std::string &id, float displacementStrength);
  static void setReinhardToneMapping(const std::string &id, bool tone_mapping);
  static void setMaterialDiffuseColor(const std::string &id, const ofColor &color);
  static void setMaterialSpecularColor(const std::string &id, const ofColor &color);
  static void setMaterialAmbientColor(const std::string &id, const ofColor &color);
};
