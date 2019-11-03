
#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
  joy_.setup(GLFW_JOYSTICK_1);

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
  ofBackground(0);
  if (joy_.isConnect()){
    for (int i=0;i<joy_.getButtonNum();i++){
      ofSetColor(joy_.isPushing(i)?255:0,0,0);
      ofDrawRectangle(20+(i*35),20,30,30);
      ofSetColor(255,255,255);
      ofDrawBitmapString(ofToString(i),30+(i*35),40);
    }

    for (int i=0;i<joy_.getAxisNum();i++){
      ofSetColor(160,160,160);
      ofDrawLine(20+(i*45), 80, 60+(i*45), 80);
      ofDrawLine(60+(i*45), 80, 60+(i*45), 180);
      ofDrawLine(20+(i*45), 180, 60+(i*45), 180);
      ofDrawLine(20+(i*45), 80, 20+(i*45), 180);
      ofSetColor(255,255,255);
      ofDrawLine(20+(i*45), 80+((joy_.getAxis(i)+1.0f)*50.0f), 60+(i*45), 80+((joy_.getAxis(i)+1.0f)*50.0f));   
      ofDrawBitmapString(ofToString(i),30+(i*45),160);
    }

    ofDrawBitmapString(joy_.getName(),30,220);
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
