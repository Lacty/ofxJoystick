
#include "ofxJoystick.h"


void ofxJoystick::updateState() {
  isConnect_ = (glfwJoystickPresent(id_) == GL_TRUE);
  if (isConnect_) {
    name_ = glfwGetJoystickName(id_);
  }
}
  
void ofxJoystick::updateAxis() {
  const float* axis = glfwGetJoystickAxes(id_, &axisNum_);
  axis_ = vector<float>(&axis[0], &axis[axisNum_]);
}
  
void ofxJoystick::updateButton() {
  pressed_.clear();
  release_.clear();
  
  const unsigned char* button = glfwGetJoystickButtons(id_, &buttonNum_);
  
  for (int i = 0; i < buttonNum_; i++) {
    switch(button[i]) {
      case GLFW_PRESS : {
        if (pushing_.find(i) == pushing_.end()) {
          pressed_.emplace(i);
        }
        pushing_.emplace(i);
        break;
      }
      case GLFW_RELEASE : {
        if (pushing_.find(i) != pushing_.end()) {
          release_.emplace(i);
          pushing_.erase(pushing_.find(i));
        }
        break;
      }
    }
  }
}

void ofxJoystick::setup(int JoyId) {
  id_   = JoyId;

  updateState();
  if (!isConnect_) {
    ofLog() << "Joypad [" << id_ << "] : disconnected";
    return;
  }
  
  name_ = glfwGetJoystickName(id_);
  glfwGetJoystickButtons(id_, &buttonNum_);
  glfwGetJoystickAxes(id_, &axisNum_);

  ofLog() << "JoyPad connected : " << name_;
  ofLog() << "Button Num : " << buttonNum_;
  ofLog() << "Axis Num : " << axisNum_ << endl;
}
  
void ofxJoystick::update() {
  updateState();
  updateAxis();
  updateButton();
}
  
bool ofxJoystick::isConnect() const {
  return isConnect_;
}

int ofxJoystick::getId() const {
  return id_;
}

const string& ofxJoystick::getName() const {
  return name_;
}
  
int ofxJoystick::getButtonNum() const {
  return buttonNum_;
}
  
int ofxJoystick::getAxisNum() const {
  return axisNum_;
}
  
float ofxJoystick::getAxis(int num) const {
  if (!isConnect_) return 0;
  if (num > axisNum_) return 0;
  return axis_[num];
}
  
bool ofxJoystick::isPressed(int button) const {
  if (pressed_.find(button) == pressed_.end()) {
    return false;
  }
  return true;
}
  
bool ofxJoystick::isPushing(int button) const {
  if (pushing_.find(button) == pushing_.end()) {
    return false;
  }
  return true;
}
  
bool ofxJoystick::isRelease(int button) const {
  if (release_.find(button) == release_.end()) {
    return false;
  }
  return true;
}