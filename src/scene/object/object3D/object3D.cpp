#include "object3D.h"

#include "constants.h"

void Object3D::draw(bool isSelected, bool isBoundingBoxEnable, bool isObjectAxisEnable) {
  this->updateProperties();
  ofPushStyle();
  if (isSelected) {
    ofSetColor(Constants::SELECTED_OBJECT_FRAME_COLOR);
    primitive->drawWireframe();

    if (isBoundingBoxEnable) {
      this->drawBoundingBox();
    }

    if (isObjectAxisEnable) {
      this->drawAxis();
    }
  }
  ofSetColor(this->getPropertyValue<ofColor>(PROPERTY_ID::COLOR));

  if (!this->getPropertyValue<bool>(PROPERTY_ID::SHOW_WIREFRAME)) {
    if (mTex.isAllocated()) {
      this->mTex.bind();
      mMaterial.setDiffuseColor(this->getPropertyValue<ofColor>(PROPERTY_ID::COLOR));
      mMaterial.begin();
      primitive->draw();
      mMaterial.end();
      this->mTex.unbind();
    } else {
      mMaterial.setDiffuseColor(this->getPropertyValue<ofColor>(PROPERTY_ID::COLOR));
      mMaterial.begin();
      primitive->draw();
      mMaterial.end();
    }

  } else {
    ofNoFill();
    // primitive->draw();
    primitive->drawWireframe();
  }
  ofPopStyle();
}

void Object3D::drawAxis() {
  ofVec3f xAxis = this->primitive->getXAxis();
  ofVec3f yAxis = this->primitive->getYAxis();
  ofVec3f zAxis = this->primitive->getZAxis();

  auto vecScale = this->primitive->getScale();
  auto vecRescale = vecScale * (1.25f * Constants::DEFAULT_SIZE);
  float scaleHeadArrow = vecRescale.x / 8;
  ofPushStyle();
  ofPushMatrix();

  ofTranslate(this->position);
  ofSetColor(ofColor::red);
  ofDrawArrow(ofPoint(0), ofPoint(xAxis * vecRescale.x), scaleHeadArrow);

  ofSetColor(ofColor::green);
  ofDrawArrow(ofPoint(0), ofPoint(yAxis * vecRescale.y), scaleHeadArrow);

  ofSetColor(ofColor::blue);
  ofDrawArrow(ofPoint(0), ofPoint(zAxis * vecRescale.z), scaleHeadArrow);

  ofPopMatrix();
  ofPopStyle();
}

void Object3D::drawBoundingBox() {
  ofPushStyle();
  ofNoFill();
  ofSetColor(ofColor::yellow);

  this->drawAABB();

  ofPopStyle();
}

void Object3D::drawAABB() const {
  vector<glm::vec3> vertices = this->primitive.get()->getMesh().getVertices();
  if (vertices.empty()) {
    return;
  }

  ofQuaternion rotation = primitive->getOrientationQuat();
  ofVec3f scale = primitive->getScale();

  for (auto &vertex : vertices) {
    vertex *= scale;
    vertex = rotation * vertex;
  }

  ofVec3f minBound(vertices[0]), maxBound(vertices[0]);
  for (const auto &vertex : vertices) {
    minBound.x = min(minBound.x, vertex.x);
    minBound.y = min(minBound.y, vertex.y);
    minBound.z = min(minBound.z, vertex.z);

    maxBound.x = max(maxBound.x, vertex.x);
    maxBound.y = max(maxBound.y, vertex.y);
    maxBound.z = max(maxBound.z, vertex.z);
  }

  ofVec3f center = ofVec3f(
      (maxBound.x + minBound.x) / 2,
      (maxBound.y + minBound.y) / 2,
      (maxBound.z + minBound.z) / 2);

  center += this->primitive.get()->getGlobalPosition();

  ofVec3f boundingBoxDimensions = maxBound - minBound;

  ofDrawBox(center.x, center.y, center.z, boundingBoxDimensions.x, boundingBoxDimensions.y, boundingBoxDimensions.z);
}