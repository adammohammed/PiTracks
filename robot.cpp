#include <iostream>
#include <unistd.h>

#include <opencv2/core.hpp>

#include "robot.h"
#include "SerialInterface.h"

using namespace std;

Robot::Robot(std::string device){
  int fd = OpenArduinoSerial((char const * const) device.c_str());
  if (fd <= 0){
    cout << "Couldn't open Serial device" << endl;
  }

  serial = fd;
}

void Robot::Forward() {
  write(serial, "w", 2);
}

void Robot::Reverse() {
  write(serial, "s", 2);
}

void Robot::Left() {
  write(serial, "a", 2);
}

void Robot::Right() {
  write(serial, "d", 2);
}

void Robot::Update(cv::Point pos) {
  int x = (int) pos.x > 0 ? pos.x : width/2;
  int y = (int) pos.y > 0 ? pos.y : height/2;
  if (x < leftLimit){
    Left();
  }else if ( x > rightLimit){
    Right();
  }
}

void Robot::setFrameWidth(const int w){
  width = w;
  leftLimit = w * ratio;
  rightLimit = w * (1 - ratio);
}
void Robot::setFrameHeight(const int h){
  height = h;
}
