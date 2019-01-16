#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <online_map_coverage/online_map_coverage.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "online_map_coverage_node");

  Mat img= imread("/home/nvidia/catkin_ws/src/online_map_coverage/a");
  
  if(img.empty()){
    ROS_INFO("Load image failed!");
    return 0;
  }
  Mat img_R;
  cvtColor(img,img_R,CV_BGR2GRAY);//change 3 dimensional image into one D gray scale
  namedWindow("Gray_Window");
  imshow("Gray_Window", img_R);
  Mat img_b;
  threshold(img_R,img_b,0,1,THRESH_BINARY_INV);//transformation of gray image into binary image
  namedWindow("Bin_Window");
  imshow("Bin_Window", img_b);
  int cells=0;
  Mat separate_map=OC::calc_bcd(img_b,cells);
  ROS_INFO("Separate image sucessed!");
  Mat display_mat=OC::display_separate_map(separate_map,cells);
  ROS_INFO("Display Separate image sucessed!");
  namedWindow("OC_Window");
  imshow("OC_Window", display_mat);
  cvWaitKey(0);
  return 1;
}


