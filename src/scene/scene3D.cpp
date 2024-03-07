﻿#include "scene3D.h"

#include "constants.h"

void Scene3D::setup() {
  this->sphere.enableTextures();
  this->ray = Ray();

  // Initialize light
  this->light.setAmbientColor(Constants::AMBIANT_COLOR);
  this->light.setPosition(Constants::LIGHT_POSITION);
  ofEnableSmoothing();
  ofEnableLighting();
  this->light.enable();

  // Initialize camera
  this->setupPerspectiveCamera();
  this->setupOrthographicCamera();

  this->currentCamera = this->perspectiveCamera.get();
}

void Scene3D::drawScene() {
  this->cursor->drawCursor(ofGetMouseX(), ofGetMouseY());

  this->currentCamera->begin();

  ofDrawGrid(10, 100, false, false, true, false);
  ofDrawSphere(0, 0, 0, 1); // Draw (0,0,0)
  this->sceneManager.get()->drawScene();

  this->processMouseActions();

  this->currentCamera->end();
}

void Scene3D::toggleProjectionMode() {
  if (this->currentCamera->getOrtho()) {
    this->perspectiveCamera.get()->enableMouseInput();
    this->orthographicCamera.get()->disableMouseInput();
    this->currentCamera = this->perspectiveCamera.get();
  } else {
    this->perspectiveCamera.get()->disableMouseInput();
    this->orthographicCamera.get()->enableMouseInput();
    this->currentCamera = this->orthographicCamera.get();
  }
}

void Scene3D::processMouseActions() {
  if (this->shouldDragObject) {
    this->currentCamera->disableMouseInput();
  }

  if (!isMouseClickInScene()) {
    this->currentCamera->disableMouseInput();
    return;
  }
  const float distance = Constants::DEFAULT_DISTANCE_TO_DRAW_PRIMITIVE;

  if (this->cursor->getCursorMode() == CursorMode::ADDING) {
    auto &&maybeObject = this->cursor->setRayWithCollidingObject(this->sceneManager.get()->getObjects(), *this->currentCamera, this->ray);
    auto &&found = maybeObject.has_value();
    auto position = this->ray.getOrigin() + this->ray.getDirection() * distance;

    if (!found) {
      this->ray.drawPrimitiveDefaultPreview(this->currentObjectToAdd, position);
    }
  }

  if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
    shouldDragObject = false;
    this->currentCamera->enableMouseInput();
  }

  if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
    auto &&maybeObject = this->cursor->setRayWithCollidingObject(this->sceneManager.get()->getObjects(), *this->currentCamera, this->ray);
    auto &&found = maybeObject.has_value();

    if (found) {
      auto it = std::find(this->sceneManager.get()->getSelectedObjects().begin(), this->sceneManager.get()->getSelectedObjects().end(), maybeObject.value());

      if (it != this->sceneManager.get()->getSelectedObjects().end()) {
        draggedObject = *it;
        shouldDragObject = true;
      }
    }

    if (found && this->cursor->getCursorMode() == CursorMode::NAVIGATION) {
      if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_LeftCtrl))) {
        this->sceneManager.get()->clickSelectionSceneObject(maybeObject.value());
      } else {
        this->sceneManager.get()->setSelectedSceneObject(maybeObject.value());
      }

    } else if (found && this->cursor->getCursorMode() == CursorMode::REMOVING) {
      this->sceneManager.get()->removeObject(maybeObject.value());
      this->cursor->setCursorMode(CursorMode::NAVIGATION);

    } else if (this->cursor->getCursorMode() == CursorMode::ADDING) {
      this->sceneManager.get()->addElement(this->ray.getOrigin() + this->ray.getDirection() * distance, this->currentObjectToAdd);
      this->cursor->setCursorMode(CursorMode::NAVIGATION);
      this->sceneManager.get()->setSelectedSceneObject(this->sceneManager.get()->getObjects().back().get());
    }
  }

  if (ImGui::IsMouseDown(ImGuiMouseButton_Left)
      && shouldDragObject
      && this->cursor->getCursorMode() == CursorMode::NAVIGATION) {
    this->cursor->computeRay(*this->currentCamera, this->ray);
    this->sceneManager.get()->setObjectPosition(this->draggedObject, ray.getOrigin() + ray.getDirection() * distance);
    this->currentCamera->disableMouseInput();
  }
}

void Scene3D::setupPerspectiveCamera() {
  this->perspectiveCamera = std::make_unique<ofEasyCam>();

  this->perspectiveCamera.get()->setPosition(200, 50, 200);
  this->perspectiveCamera.get()->lookAt(glm::vec3(0, 0, 0));
}

void Scene3D::setupOrthographicCamera() {
  this->orthographicCamera = std::make_unique<ofEasyCam>();
  this->orthographicCamera.get()->enableOrtho();

  this->orthographicCamera.get()->setPosition(10, 5, 10);
  this->orthographicCamera.get()->lookAt(glm::vec3(0, 0, 0));

  this->orthographicCamera.get()->removeAllInteractions();
  this->orthographicCamera.get()->addInteraction(ofEasyCam::TRANSFORM_TRANSLATE_XY, OF_MOUSE_BUTTON_LEFT);
  this->orthographicCamera.get()->addInteraction(ofEasyCam::TRANSFORM_TRANSLATE_Z, OF_MOUSE_BUTTON_RIGHT);

  this->orthographicCamera.get()->setNearClip(-1000000);
  this->orthographicCamera.get()->setFarClip(1000000);
}
