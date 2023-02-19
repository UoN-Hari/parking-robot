#ifndef PLATE_LOCALIZATION_H
#define PLATE_LOCALIZATION_H

#include "ros/ros.h"
#include "sensor_msgs/CompressedImage.h"
#include "sensor_msgs/image_encodings.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include "geometry_msgs/PoseStamped.h"
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <iostream>

class SubPuber
{
private:

  ros::NodeHandle nodeHandle;
  ros::Subscriber cameraImageSub;
  ros::Publisher recognizedImagePub;
  ros::Publisher platePosePub;

public:

  SubPuber(){
    // 获取相机话题
    std::string cameraTopic;
    ros::param::get("CameraTopic", cameraTopic);
    // 订阅相机话题，此处默认为realsense彩色图像的topic
    cameraImageSub = nodeHandle.subscribe(cameraTopic, 1, &SubPuber::PlateRecognitionCallback, this);
    // 发布框选出车牌后的图像
    recognizedImagePub = nodeHandle.advertise<sensor_msgs::Image>("/recognized_image", 1);
    // 发布识别结果
    platePosePub = nodeHandle.advertise<geometry_msgs::PoseStamped>("/plate_pose", 1);
  }

  void PlateRecognitionCallback(const sensor_msgs::ImageConstPtr &cameraImage);
};

#endif