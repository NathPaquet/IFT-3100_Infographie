#include "TextureRepository.h"

static std::list<std::unique_ptr<TexturePack>> textures;

void TextureRepository::addTexture(const std::string &packName) {
  textures.push_back(std::make_unique<TexturePack>(packName));
}

void TextureRepository::addTextureFromSingleImage(const ofImage &image, const std::string &id) {
  textures.push_back(std::make_unique<TexturePack>(image, id));
}

const std::list<std::unique_ptr<TexturePack>> &TextureRepository::getTextures() {
  return textures;
}

void TextureRepository::configureTextureWithShader(const std::string &id, std::shared_ptr<ofShader> shader) {
  auto it = std::find_if(textures.begin(), textures.end(), [&](auto &&element) { return element->packId == id; });
  it->get()->configureMaterial(shader);
}

const TexturePack *TextureRepository::getTexture(const std::string &packId) {
  auto it = std::find_if(getTextures().begin(), getTextures().end(), [&](auto &&element) { return element->packId == packId; });
  if (it == getTextures().end()) {
    return nullptr;
  }
  return it->get();
}

void TextureRepository::setDisplacementMap(const std::string &id, const ofTexture &texture) {
  auto it = std::find_if(textures.begin(), textures.end(), [&](auto &&element) { return element->packId == id; });
  if (it == textures.end()) {
    return;
  }
  it->get()->setDisplacementTexture(texture);
}

void TextureRepository::setTextureDiffuseMap(std::function<void(ofTexture &)> callback, const std::string &id) {
  auto it = std::find_if(textures.begin(), textures.end(), [&](auto &&element) { return element->packId == id; });
  callback(it->get()->textureDiffuseMap);
}

void TextureRepository::setMetallicity(const std::string &id, float metallicity) {
  auto it = std::find_if(textures.begin(), textures.end(), [&](auto &&element) { return element->packId == id; });
  it->get()->setMetallicity(metallicity);
}

void TextureRepository::setRoughness(const std::string &id, float roughness) {
  auto it = std::find_if(textures.begin(), textures.end(), [&](auto &&element) { return element->packId == id; });
  it->get()->setRoughness(roughness);
}

void TextureRepository::setBrightness(const std::string &id, float brightness) {
  auto it = std::find_if(textures.begin(), textures.end(), [&](auto &&element) { return element->packId == id; });
  it->get()->setBrightness(brightness);
}

void TextureRepository::setDisplacementStrength(const std::string &id, float displacementStrength) {
  auto it = std::find_if(textures.begin(), textures.end(), [&](auto &&element) { return element->packId == id; });
  it->get()->setDisplacementStrength(displacementStrength);
}

void TextureRepository::setReinhardToneMapping(const std::string &id, bool tone_mapping) {
  auto it = std::find_if(textures.begin(), textures.end(), [&](auto &&element) { return element->packId == id; });
  it->get()->setReinhardToneMapping(tone_mapping);
}

void TextureRepository::setMaterialDiffuseColor(const std::string &id, const ofColor &color) {
  auto it = std::find_if(textures.begin(), textures.end(), [&](auto &&element) { return element->packId == id; });
  it->get()->setMaterialDiffuseColor(color);
}

void TextureRepository::setMaterialSpecularColor(const std::string &id, const ofColor &color) {
  auto it = std::find_if(textures.begin(), textures.end(), [&](auto &&element) { return element->packId == id; });
  it->get()->setMaterialSpecularColor(color);
}

void TextureRepository::setMaterialAmbientColor(const std::string &id, const ofColor &color) {
  auto it = std::find_if(textures.begin(), textures.end(), [&](auto &&element) { return element->packId == id; });
  it->get()->setMaterialAmbientColor(color);
}
