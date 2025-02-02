#include "Tools.h"

void Tools::createToolsMenu(Scene3D *scene3D) {
  if (ImGui::BeginMenu("Tools")) {
    if (ImGui::MenuItem("Export")) {
      showExportMenu = true;
    }

    std::string ambientLightTitle = (scene3D->isAmbientLightEnable() ? "Disable" : "Enable") + std::string(" Ambient Light");
    if (ImGui::MenuItem(ambientLightTitle.c_str())) {
      scene3D->toggleAmbientLight();
    }

    ImGui::EndMenu();
  }

  if (showExportMenu) {
    exportMenu.createExportMenu(&showExportMenu);
  }
}
