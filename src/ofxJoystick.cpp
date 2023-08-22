
#include "ofxJoystick.h"
#ifdef __linux__
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/joystick.h>
int read_event(int fd, struct js_event *event)
{
    ssize_t bytes;

    bytes = read(fd, event, sizeof(*event));

    if (bytes == sizeof(*event))
        return 0;

    /* Error, could not read full event. */
    return -1;
}

/**
 * Returns the number of axes on the controller or 0 if an error occurs.
 */
size_t get_axis_count(int fd)
{
    __u8 axes;

    if (ioctl(fd, JSIOCGAXES, &axes) == -1)
        return 0;

    return axes;
}

/**
 * Returns the number of buttons on the controller or 0 if an error occurs.
 */
size_t get_button_count(int fd)
{
    __u8 buttons;
    if (ioctl(fd, JSIOCGBUTTONS, &buttons) == -1)
        return 0;

    return buttons;
}

size_t get_axis_state(struct js_event *event, struct axis_state axes[3])
{
    size_t axis = event->number / 2;

    if (axis < 3)
    {
        if (event->number % 2 == 0)
            axes[axis].x = event->value/32767.f;
        else
            axes[axis].y = event->value/32767.f;
    }

    return axis;
}

#endif

ofxJoystick::~ofxJoystick() {
  ofRemoveListener(ofEvents().update, this, &ofxJoystick::update);
}

void ofxJoystick::updateState() {
#ifdef __linux__
  if (isConnect_ == false)
  {
    char device[255];
    if (js_ != -1)
    {
        close(js_);
    }

    sprintf(device,"/dev/input/js%d", id_);
    js_ = open(device,O_RDONLY | O_NONBLOCK);
    name_= std::string(device);
    printf("\n");
    if (js_ == -1)
        return;

    isConnect_ = true;
    //perror("Could not open joystick");

    struct JS_DATA_TYPE jso;
    if(read(js_, &jso, JS_RETURN))
    {
        printf("%x\n", jso.buttons );
        if(jso.buttons == 0)
        {
          // No Bridge detected
          printf("Port %d - Detected no Bridged Buttons", id_ );
          isConnect_ = false;
          close(js_);
          return;
        }
         for (int i=0;i<15;i++)
            if(jso.buttons & 1 << i)
             {
                button[i] = true;
                printf("%d Held\n",i);
            }
    }
    else
    {

    }
  }
  #else
  isConnect_ = (glfwJoystickPresent(id_) == GL_TRUE);
  if (isConnect_) {
    name_ = glfwGetJoystickName(id_);
  }



  #endif
}

void ofxJoystick::updateAxis() {
  #ifdef __linux__
  axis_.clear();
  //axis_ = vector<float>(&axes[0], &axes[axisNum_]);
  for (int axis=0; axis<axisNum_;axis++)
  {
    //std::cout <<"  "<< axes[axis].x << " " << axes[axis].y;
    axis_.push_back(axes[axis].x);
    axis_.push_back(axes[axis].y);

  }
  //std::cout << std::endl;
  #else
  const float* axis = glfwGetJoystickAxes(id_, &axisNum_);
  axis_ = vector<float>(&axis[0], &axis[axisNum_]);
#endif // __linux__
}

void ofxJoystick::updateButton() {
  pressed_.clear();
  release_.clear();
#ifdef __linux__
#else
  const unsigned char* button = glfwGetJoystickButtons(id_, &buttonNum_);
#endif
  for (int i = 0; i < buttonNum_; i++) {
    //std::cout << i << " " <<(int16_t)button[i] << "  ";
    switch(button[i]) {

      case GLFW_PRESS : {
        if (pushing_.find(i) == pushing_.end()) {
          pushing_.emplace(i);
        }
        pressed_.emplace(i);
        //std::cout << i << " Pressed!" << std::endl;
        break;
      }
      case GLFW_RELEASE : {
        if (pushing_.find(i) != pushing_.end()) {
          //std::cout  << i << " Released!" << std::endl;
          pushing_.erase(pushing_.find(i));
        }
        release_.emplace(i);
        break;
      }
      	case GLFW_REPEAT:
		{
			if (pushing_.find(i) == pushing_.end()) {
				pushing_.emplace(i);
			}
			 // std::cout << i << " Pressed!" << std::endl;
      pressed_.emplace(i);
			break;
		}
    }
  }
  //std::cout << std::endl;
}

void ofxJoystick::setup(int JoyId) {
  id_ = JoyId;

  updateState();
  if (!isConnect_) {
    //ofLog() << "Joypad [" << id_ << "] : disconnected";
    return;
  }

  #ifdef __linux__

  #else
  name_ = glfwGetJoystickName(id_);
  #endif
  //avoid crash when accessing data on first call to ofApp::update()
  updateAxis();
  updateButton();

#ifdef __linux__
  axisNum_ = get_axis_count(js_);
  buttonNum_ = get_button_count(js_);
#else
  glfwGetJoystickButtons(id_, &buttonNum_);
  glfwGetJoystickAxes(id_, &axisNum_);
#endif

  ofAddListener(ofEvents().update, this, &ofxJoystick::update);

  //ofLog() << "JoyPad connected : " << name_;
  //ofLog() << "Button Num : " << buttonNum_;
  //ofLog() << "Axis Num : " << axisNum_ << endl;

  //avoid crash when accessing data on first call to ofApp::update()
  updateAxis();
  updateButton();
}

void ofxJoystick::update(ofEventArgs &args) {
 #ifdef __linux__
  struct js_event event;

  int res = read_event(js_, &event);
  if(res == -1)
    {

        int errsv = errno;
        if (errsv != EAGAIN)
        {
            //std::cout << "Disconnected: " << id_ << std::endl;
            isConnect_ = false;
            close(js_);
            js_=-1;

        }
    }
  while ( res == 0)
    {
        //printf("event Type: %d", event.type);
        switch (event.type)
        {

            case JS_EVENT_BUTTON:
                //printf("Button %u %s\n", event.number, event.value ? "pressed" : "released");
                button[event.number] = event.value ? GLFW_PRESS : GLFW_RELEASE;
                break;
            case JS_EVENT_AXIS:
                get_axis_state(&event, axes);

                break;
            default:
                /* Ignore init events. */
                break;
        }
        res = read_event(js_, &event);
    if(res == -1)
    {

        int errsv = errno;
        if (errsv != EAGAIN)
        {
            //std::cout << "Disconnected: " << id_ << std::endl;
            isConnect_ = false;
            close(js_);
            js_=-1;
        }
    }
    }


  #endif
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

bool ofxJoystick::anyButton() const {
  if (pressed_.size()) {
    return true;
  }
  return false;
}

