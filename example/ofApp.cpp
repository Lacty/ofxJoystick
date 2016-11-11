
#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
  joy_.setup(GLFW_JOYSTICK_1);
}

//--------------------------------------------------------------
void ofApp::update() {
  joy_.update();
  
  // chack all button for push
  for (int i = 0; i < joy_.getButtonNum(); i++) {
    if (joy_.isPush(i)) {
      ofLog() << "push :" << i;
    }
  }
  
  // get left X axis
  ofLog() << "left X axis :" << joy_.getAxis(0);
  
  // get left Y axis
  ofLog() << "left Y axis :" << joy_.getAxis(1);
}

//--------------------------------------------------------------
void ofApp::draw() {}

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
