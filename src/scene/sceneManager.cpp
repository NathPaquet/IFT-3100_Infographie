#include "sceneManager.h"
#include "Planet.h"

SceneManager::SceneManager()
{
	ofLogNotice("SceneManager") << "SceneManager constructor";
}

SceneManager::~SceneManager() {
	clearScene();
}

void SceneManager::addElement(const ofVec3f &position)
{   
    // TODO : Add scene object factory here
    sceneElements.emplace_back(std::make_unique<Planet>(Planet(position.x, position.y, position.z)));
}

void SceneManager::removeElement(size_t index) {
	if (index < 0 || index >= sceneElements.size()) {
		return;
	}
	sceneElements.erase(std::next(sceneElements.begin(), index));
}

void SceneManager::drawScene() {
    for (auto &&element : sceneElements) {
        element->draw();
    }
}

void SceneManager::clearScene() {
	sceneElements.clear();
}