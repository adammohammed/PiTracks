#ifndef ROBOT_H
#define ROBOT_H

#include <opencv2/core.hpp>

class Robot {
 private:
  int serial;
  int frameWidth;
  int frameHeight;
  int leftLimit;
  int rightLimit;
  int minFaceLimit;
  int maxFaceLimit;
  double ratio = 0.33;
  void Forward();
  void Reverse();
  void Left();
  void Right();
  void Stop();
 public:
  Robot() : Robot("/dev/ttyUSB0", 0.2, 0.6){}
  Robot(std::string device) : Robot(device, 0.2, 0.6) {};
  Robot(std::string device, double lowerThreshold, double upperThreshold);
  void Update(cv::Point, double roiHeight);
  void setFrameWidth(const int w);
  void setFrameHeight(const int h);
};

#endif /* ROBOT_H */
