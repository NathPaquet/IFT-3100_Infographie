#include "ofApp.h"
#include "ImHelpers.h"
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowTitle("BasedEngine");
	ofSetLogLevel(OF_LOG_VERBOSE);
    
    //required call
    gui.setup(nullptr, true, ImGuiConfigFlags_ViewportsEnable );

    //Initialize scene manager
    sceneManager = new SceneManager();

    //backgroundColor is stored as an ImVec4 type but can handle ofColor
    backgroundColor = ofColor(114, 144, 154);
}

//--------------------------------------------------------------
void ofApp::exit() {
}

//--------------------------------------------------------------
void ofApp::update() {
	//ofSetCircleResolution(circleResolution);

}

//--------------------------------------------------------------
void ofApp::draw() {
    gui.begin();
    
    // Show the ImGui test window. Most of the sample code is in ImGui::ShowDemoWindow()
    ImGui::SetNextWindowPos( ofVec2f( ofGetWindowPositionX(), ofGetWindowPositionY()), ImGuiCond_Once);
    ImGui::SetNextWindowSize( ofVec2f(ofGetWidth(), ofGetHeight()), ImGuiCond_Once);
    ImGui::Begin("Main window !");

	if (ImGui::Button("Hello world", ImVec2(200.f, 200.f))){
		std::cout << "ahah" << std::endl;
	}
	
	ImGui::End();
	// ImGui::ShowDemoWindow();
    sceneManager->drawScene();

    //required to call this at end
    gui.end();
}
