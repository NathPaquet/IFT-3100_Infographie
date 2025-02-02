#pragma once

#include "ColorPicker.h"
#include "TexturePicker.h"

enum class TextureType {
  DIFFUSE,
  NORMAL,
  DISPLACEMENT,
  AO_ROUGH_METAL
};

class TextureEditor {
public:
  TextureEditor();
  void displayEditorOptions();
  void displayGenericOptions();
  void displayTextureSpecificOptions(const TexturePack *texture);
  void generateDisplacementMapForTexture(const TexturePack *texture);
  void drawTextureEditor();
  void setCurrentTexture(const TexturePack *texture);
  void drawImages(const TexturePack *texture);
  std::shared_ptr<ofShader> getDefaultShader();

private:
  TexturePicker texturePicker;
  ColorPicker colorPicker;
  const TexturePack *currentTexture{nullptr};
  std::shared_ptr<ofShader> defaultMaterialShader;

  bool hasBlur{false};
  bool hasSharpen{false};
  bool hasGrey{false};
  float displacementGenerationDensity = 0.01;

  bool has_reinhard_tone_mapping{false};

  void drawMaterialProperties();
};
