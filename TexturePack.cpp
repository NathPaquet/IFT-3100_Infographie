#include "TexturePack.h"

TexturePack::TexturePack(const ofImage &image, const std::string &id) {
  loadSingleImage(image, id);
}

TexturePack::TexturePack(const std::string &packName) {
  load(packName);
}

void TexturePack::loadSingleImage(const ofImage &image, const std::string &id) {
  this->packId = id;
  textureDiffuseMap = image.getTexture();
  if (textureDiffuseMap.isAllocated()) {
    configureTexture(textureDiffuseMap);
  }
}

bool TexturePack::load(const std::string &packName) {
  this->packId = packName;
  std::string filename = ofToLower(packName);

  bool was_success = ofLoadImage(textureDiffuseMap, "textures/" + packName + "/" + filename + "_diff.jpg");
  if (!was_success) {
    ofLoadImage(textureDiffuseMap, "textures/" + packName + "/" + filename + "_diff.png");
  }
  was_success = ofLoadImage(textureNormalMap, "textures/" + packName + "/" + filename + "_nor_gl.jpg");
  if (!was_success) {
    ofLoadImage(textureNormalMap, "textures/" + packName + "/" + filename + "_nor_gl.png");
  }
  was_success = ofLoadImage(textureDisplacementMap, "textures/" + packName + "/" + filename + "_disp.png");
  if (!was_success) {
    ofLoadImage(textureDisplacementMap, "textures/" + packName + "/" + filename + "_disp.jpg");
  }
  was_success = ofLoadImage(textureAORoughMetal, "textures/" + packName + "/" + filename + "_arm.jpg");
  if (!was_success) {
    ofLoadImage(textureAORoughMetal, "textures/" + packName + "/" + filename + "_arm.png");
  }

  if (textureDiffuseMap.isAllocated()) {
    configureTexture(textureDiffuseMap);
  }
  if (textureNormalMap.isAllocated()) {
    configureTexture(textureNormalMap);
  }
  if (textureDisplacementMap.isAllocated()) {
    configureTexture(textureDisplacementMap);
  }
  if (textureAORoughMetal.isAllocated()) {
    configureTexture(textureAORoughMetal);
  }

  return was_success;
}

void TexturePack::configureTexture(ofTexture &texture) {
  texture.setTextureWrap(GL_REPEAT, GL_REPEAT);
  texture.generateMipmap();

  GLfloat fLargest = 1.0;
  glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);

  texture.bind();
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  texture.unbind();
}

void TexturePack::configureMaterial(std::shared_ptr<ofShader> shader) {
  material.setCustomShader(shader);
  material.setAmbientColor(ofFloatColor(1, 1, 1, 0.6));
  // set our textures on the material so that they will be passed to our custom shader
  material.setCustomUniformTexture("mapDiffuse", textureDiffuseMap, 0);
  material.setCustomUniformTexture("mapNormal", textureNormalMap, 1);
  material.setCustomUniformTexture("mapDisplacement", textureDisplacementMap, 2);
  material.setCustomUniformTexture("mapAORoughMetal", textureAORoughMetal, 3);
}

void TexturePack::setMetallicity(float metallicity) {
  material.setMetallic(metallicity);
}

void TexturePack::setRoughness(float roughness) {
  material.setRoughness(roughness);
}

float TexturePack::getMetallicity() const {
  return material.getMetallic();
}

float TexturePack::getRoughness() const {
  return material.getRoughness();
}
