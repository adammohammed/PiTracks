#include <unistd.h>

#include "SerialInterface.h"

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include "robot.h"
#include "VideoFaceDetector.h"


const cv::String    WINDOW_NAME("Camera video");
const cv::String    CASCADE_FILE("haarcascade_frontalface_default.xml");

int main(int argc, char **argv)
{
  if (argc < 2) {
    printf("USAGE: ./%s <device_location>\n\t\te.g. ./%s /dev/ttyUSB0\n", argv[0], argv[0]);
    return -1;
  }
  Robot robot(argv[1]);

  cv::VideoCapture camera(0);
  int ct = 0;
  //cv::VideoCapture camera("D:\\video.mp4");
  if (!camera.isOpened()) {
    fprintf(stderr, "Error getting camera...\n");
    exit(1);
  }

  cv::namedWindow(WINDOW_NAME, cv::WINDOW_KEEPRATIO | cv::WINDOW_AUTOSIZE);

  VideoFaceDetector detector(CASCADE_FILE, camera);
  cv::Mat frame;
  double fps = 0, time_per_frame;

  detector >> frame;
  robot.setFrameWidth(frame.size().width);
  robot.setFrameHeight(frame.size().height);
  while (true)
    {
      auto start = cv::getCPUTickCount();
      detector >> frame;
      auto end = cv::getCPUTickCount();

      time_per_frame = (end - start) / cv::getTickFrequency();
      fps = (15 * fps + (1 / time_per_frame)) / 16;

      if(ct == 100){
        printf("Time per frame: %3.3f\tFPS: %3.3f\n", time_per_frame, fps);
        ct = 0;
      } else {
        ct++;
      }

      if (detector.isFaceFound())
        {
          cv::rectangle(frame, detector.face(), cv::Scalar(255, 0, 0));
          cv::circle(frame, detector.facePosition(), 30, cv::Scalar(0, 255, 0));
          robot.Update(detector.facePosition(), detector.face().height);
        }

      cv::imshow(WINDOW_NAME, frame);
      if (cv::waitKey(28) == 27) break;
    }
  return 0;
}
