#ifndef ROBOT_H
#define ROBOT_H

#include <opencv2/core.hpp>

class Robot {
 private:
  int serial;
  int width;
  int height;
  int leftLimit;
  int rightLimit;
  double ratio = 0.33;
  void Forward();
  void Reverse();
  void Left();
  void Right();
  void Stop();
 public:
  Robot() : Robot("/dev/ttyUSB0"){}
  Robot(std::string device);
  void Update(cv::Point);
  void setFrameWidth(const int w);
  void setFrameHeight(const int h);
};

#endif /* ROBOT_H */
