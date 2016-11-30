# ofxJoystick

## usage
```cpp
// in header
ofxJoystick joy_;

// in yourApp::setup()
joy_.setup(GLFW_JOYSTICK_1);

// now get axis from your Gamepad!
float XAxis = joy_.getAxis(0);
float YAxis = joy_.getAxis(1);

// and get button input
if (joy_.isPressed(0)) { ofLog() << "pressed 0"; }
if (joy_.isPushing(0)) { ofLog() << "pushing 0"; }
if (joy_.isRelease(0)) { ofLog() << "release 0"; }
```

## my another ofxAddon
[ofxKeyboard](https://github.com/Lacty/ofxKeyboard) for KeyInput in !yourApp::keyPressed

## contact
**@Lost206** -twitter    
**akira206@gmail.com** -gmail

## lisence
ofxJoystick under MIT lisence    
