#ifndef SUBPUBER_NODE_H
#define SUBPUBER_NODE_H

#include <mcu_serial/motor_msgs.h>

#include "ros/ros.h"
#include "sensor_msgs/CompressedImage.h"
#include "sensor_msgs/image_encodings.h"
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <iostream>

class SubPuber
{
private:

  ros::NodeHandle nodeHandle;

  // ros::Subscriber topicSuber0;
  ros::Publisher topicPuber0;

  // std::string subTopic0;
  std::string pubTopic0;

  double linearSpd;
  double angularSpd;

  double rectLength;
  double rectWidth;

public:

  SubPuber(){
    // ros::param::get("SubTopic0", subTopic0);
    ros::param::get("PubTopic0", pubTopic0);
    ros::param::get("LinearSpd", linearSpd);
    ros::param::get("AngularSpd", angularSpd);

    ros::param::get("RectLength", rectLength);
    ros::param::get("RectWidth", rectWidth);

    // topicSuber0 = nodeHandle.subscribe(subTopic0, 1, &SubPuber::MovementCalculationCallback, this);
    topicPuber0 = nodeHandle.advertise<geometry_msgs::Twist>(pubTopic0, 1);
    ROS_INFO("CONSTRUCTED");
  }

  void MotionControlCallBack();
  // void Callback1(const geometry_msgs::Twist &cmdVel);
};

#endif