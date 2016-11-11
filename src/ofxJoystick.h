
#pragma once
#include "ofMain.h"


class ofxJoystick {
private:
  bool isConnect_;

  int    id_;
  string name_;

  int buttonNum_;
  int axisNum_;
  
  set<int> push_;
  set<int> press_;
  set<int> release_;
  
  vector<float> axis_;
  
  void updateState();
  void updateAxis();
  void updateButton();

public:
  ofxJoystick() = default;
  
  // JoyId : usually give GLFW_SOYSTICK_1
  // when you connect only one Gamepad
  void setup(int JoyId);

  // update() should call in yourApp::update()
  void update();

  // if connected return true
  // disconnected return false
  bool isConnect() const;

  int getId() const;
  
  // return your Gamepad name
  const string& getName() const;

  // return number of Button and Axis
  int getButtonNum() const;
  int getAxisNum() const;
  
  // return axis, if disconnected return 0
  float getAxis(int num) const;
  
  // button func
  bool isPush(int button) const;
  bool isPress(int button) const;
  bool isRelease(int button) const;
};