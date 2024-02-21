#include "ImageImporter.h"

void ImageImporter::importImage(std::vector<PropertyBase *> objectsProperty) {
  ofFileDialogResult result = ofSystemLoadDialog("Load file");
  if (result.bSuccess) {
    string pathToLoad = result.getPath();
    for (auto &&objectProperty : objectsProperty) {
      auto property = dynamic_cast<Property<ofImage> *>(objectProperty);

      if (property->getValue().load(pathToLoad)) {
        property->setChanged(true);
        ofLogNotice("ofApp") << "Image loaded successfully from: " << pathToLoad;
      } else {
        ofLogError("ofApp") << "Failed to load image from: " << pathToLoad;
      }
    }
  }
}
