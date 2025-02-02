#include "skybox.h"

#include "constants.h"

Skybox::Skybox() {
  this->skyboxShader.load("shaders/skybox.vert", "shaders/skybox.frag");
  this->cubemapTexture.setCubemapTexturePath(Constants::CUBEMAP_TEXTURE_SKYBOX_LIGHTBLUE);
  this->cubemapTexture.startThread();
}

void Skybox::loadTexture(const string &texturePath) {
  this->isCubemapLoaded = false;
  this->cubemapTexture.setCubemapTexturePath(texturePath);
  this->cubemapTexture.startThread();
}

void Skybox::draw(const float &size, const glm::vec3 &cameraPosition) const {
  if (this->isCubemapLoaded) {
    skyboxShader.begin();
    skyboxShader.setUniform1i("skybox", 0);

    ofDisableDepthTest();

    glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemapTexture.getTextureObjectID());

    ofDrawBox(cameraPosition.x, cameraPosition.y, cameraPosition.z, size);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    ofEnableDepthTest();

    skyboxShader.end();
  }
}

bool Skybox::isSkyboxLoaded() {
  if (!this->isCubemapLoaded) {
    this->isCubemapLoaded = this->cubemapTexture.enableCubemapTextures();
  }
  return this->isCubemapLoaded;
}

bool Skybox::isEnabled() const {
  return this->isSkyboxEnabled;
}

const unsigned int Skybox::getTextureObjectID() const {
  return this->cubemapTexture.getTextureObjectID();
}

void Skybox::toggleSkyboxActivation() {
  this->isSkyboxEnabled = !this->isSkyboxEnabled;
}
