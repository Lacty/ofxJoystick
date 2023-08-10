
#pragma once
#include "ofMain.h"

#include "GLFW/glfw3.h"
struct axis_state {
    short x, y;
};

class ofxJoystick {
private:
  bool isConnect_;
#ifdef __linux__
    int js_;


    struct axis_state axes[3] = {0};
    unsigned char button[256] = {0};

#endif // __linux__
  int    id_;
  string name_;

  int buttonNum_;
  int axisNum_;

  set<int> pressed_;
  set<int> pushing_;
  set<int> release_;

  vector<float> axis_;

  void updateState();
  void updateAxis();
  void updateButton();

  void update(ofEventArgs &args);

public:
  ofxJoystick() = default;
  ~ofxJoystick();

  // JoyId : usually give GLFW_SOYSTICK_1
  // when you connect only one Gamepad
  void setup(int JoyId);

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
  bool isPressed(int button) const;
  bool isPushing(int button) const;
  bool isRelease(int button) const;

  bool anyButton() const;
};
