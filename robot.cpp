#include <iostream>
#include <unistd.h>

#include <opencv2/core.hpp>

#include "robot.h"
#include "SerialInterface.h"

using namespace std;

Robot::Robot(std::string device, double lowerThreshold, double upperThreshold){
#ifndef DEBUG
  int fd = OpenArduinoSerial((char const * const) device.c_str());
  if (fd <= 0){
    cout << "Couldn't open Serial device" << endl;
  }

  serial = fd;
#endif
}

void Robot::Forward() {
#ifndef DEBUG
  write(serial, "w", 2);
#else
  cout << "Driving Forward" << endl;
#endif
}

void Robot::Reverse() {
#ifndef DEBUG
  write(serial, "s", 2);
#else
  cout << "Driving Reverse" << endl;
#endif
}

void Robot::Left() {
#ifndef DEBUG
  write(serial, "a", 2);
#else
  cout << "Driving Left" << endl;
#endif
}

void Robot::Right() {
#ifndef DEBUG
  write(serial, "d", 2);
#else
  cout << "Driving Right" << endl;
#endif
}

void Robot::Update(cv::Point pos, double roiHeight) {
  int x = (int) pos.x > 0 ? pos.x : frameWidth/2;
  int y = (int) pos.y > 0 ? pos.y : frameHeight/2;

  if (x < leftLimit){
    Left();
  }else if ( x > rightLimit){
    Right();
  }

  if (roiHeight < minFaceLimit) {
    Forward();
  } else if ( roiHeight > maxFaceLimit) {
    Reverse();
  }
}

void Robot::setFrameWidth(const int w){
  frameWidth = w;
  leftLimit = w * ratio;
  rightLimit = w * (1 - ratio);
}
void Robot::setFrameHeight(const int h){
  frameHeight = h;
  minFaceLimit = 0.2 * h;
  maxFaceLimit = 0.6 * h;
}
