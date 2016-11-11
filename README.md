# ofxJoystick

## usage
```cpp
// in header
ofxJoystick joy_;

// in yourApp::setup()
joy_.setup(GLFW_JOYSTICK_1);

// in yourApp::update()
joy_.update();

// now get axis from your Gamepad!
float XAxis = joy_.getAxis(0);
float YAxis = joy_.getAxis(1);

// and get button input
if (joy_.isPush(0))    { ofLog() << "push 0";    }
if (joy_.isPress(0))   { ofLog() << "press 0";   }
if (joy_.isRelease(0)) { ofLog() << "release 0"; }
```