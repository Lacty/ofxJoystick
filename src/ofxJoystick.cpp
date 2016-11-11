
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
  push_.clear();
  release_.clear();
  
  const unsigned char* button = glfwGetJoystickButtons(id_, &buttonNum_);
  
  for (int i = 0; i < buttonNum_; i++) {
    switch(button[i]) {
      case GLFW_PRESS : {
        if (press_.find(i) == press_.end()) {
          push_.emplace(i);
        }
        press_.emplace(i);
        break;
      }
      case GLFW_RELEASE : {
        if (press_.find(i) != press_.end()) {
          release_.emplace(i);
          press_.erase(press_.find(i));
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
  
bool ofxJoystick::isPush(int button) const {
  if (push_.find(button) == push_.end()) {
    return false;
  }
  return true;
}
  
bool ofxJoystick::isPress(int button) const {
  if (press_.find(button) == press_.end()) {
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