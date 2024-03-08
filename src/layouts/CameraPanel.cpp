#include "CameraPanel.h"

CameraPanel::CameraPanel(SceneManager *sceneManager, WindowCamera *windowCamera):
    sceneManager(sceneManager), windowCamera(windowCamera){};

void CameraPanel::setSceneManager(SceneManager *sceneManager) {
  this->sceneManager = sceneManager;
  windowCamera->setSelectedCamera(nullptr);
  this->isWindowCameraShown = false;
  windowCamera->setIsShown(isWindowCameraShown);
}

void CameraPanel::create() {
  if (ImGui::BeginMenu("Cameras")) {
    auto &cameras = sceneManager->getCameras();

    if (cameras.empty()) {
      ImGui::Text("No cameras");
    } else {
      for (int i = 0; i < cameras.size(); i++) {
        int index = i + 1;

        std::string cameraName = "Camera " + std::to_string(index);
        if (ImGui::MenuItem(cameraName.c_str())) {
          windowCamera->setSelectedCamera(cameras.at(i));
        }
      }
    }

    if (ImGui::Checkbox("Show camera view", &isWindowCameraShown)) {
      windowCamera->setIsShown(isWindowCameraShown);
    }

    ImGui::EndMenu();
  }
}
