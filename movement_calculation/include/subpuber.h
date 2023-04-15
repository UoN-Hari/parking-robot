#ifndef SUBPUBER_NODE_H
#define SUBPUBER_NODE_H

#include <mcu_serial/motor_msgs.h>

#include "ros/ros.h"
#include "sensor_msgs/CompressedImage.h"
#include "sensor_msgs/image_encodings.h"
#include <geometry_msgs/Twist.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <iostream>

class SubPuber
{
private:

  ros::NodeHandle nodeHandle;

  ros::Subscriber topicSuber0;
  ros::Publisher topicPuber0;
  // ros::Subscriber topicSuber1;
  // ros::Publisher topicPuber1;

  std::string subTopic0;
  std::string pubTopic0;
  // std::string subTopic1;
  // std::string pubTopic1;

  double lrOffset;      // Right wheel offset ratio refers to Left wheel
  double motorOffset;   // Unit offset from /cmd_vel (m/s) to /motor_cmd (rpm)
  double angularOffset; // Unit offset from angular velocity (rad/s) to wheel spd (m/s)
                        // Should be half of axle (Theoretically)

public:

  SubPuber(){
    ros::param::get("SubTopic0", subTopic0);
    ros::param::get("PubTopic0", pubTopic0);
    ros::param::get("LROffset", lrOffset);
    ros::param::get("MotorOffset", motorOffset);
    ros::param::get("AngularOffset", angularOffset);
    // ros::param::get("SubTopic1", subTopic1);
    // ros::param::get("PubTopic1", pubTopic1);

    topicSuber0 = nodeHandle.subscribe(subTopic0, 1, &SubPuber::MovementCalculationCallback, this);
    topicPuber0 = nodeHandle.advertise<mcu_serial::motor_msgs>(pubTopic0, 1);
    // topicSuber1 = nodeHandle.subscribe(subTopic1, 1, &SubPuber::Callback1, this);
    // topicPuber1 = nodeHandle.advertise<geometry_msgs::Twist>(pubTopic1, 1);
  }

  void MovementCalculationCallback(const geometry_msgs::Twist &cmdVel);
  // void Callback1(const geometry_msgs::Twist &cmdVel);
};

#endif