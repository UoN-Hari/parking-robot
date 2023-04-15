#include "subpuber.h"

void SubPuber::MovementCalculationCallback(const geometry_msgs::Twist &cmdVel)
{
  mcu_serial::motor_msgs motorCmdVel;
  // ROS_INFO("offset: %d, cmdVel.linear.x: %f, cmdVel.angular.z: %f", angularL, cmdVel.linear.x, cmdVel.angular.z);
  double angularL = motorOffset * (cmdVel.linear.x - angularOffset * cmdVel.angular.z);
  double angularR = motorOffset * (cmdVel.linear.x + angularOffset * cmdVel.angular.z);

  if(angularL - (int)angularL != 0 ||
     angularR - (int)angularR != 0 ) {
      ros::Exception("MOTOR SPEED NOT INT!!!!!!!!!!!!!!");
  }

  motorCmdVel.angular1 = angularL;
  motorCmdVel.angular2 = angularR;

  // Right wheel offset ratio refers to Left wheel
  motorCmdVel.angular2 *= lrOffset;

  // ROS_INFO("Angular1: %d", motorCmdVel.angular1);
  // ROS_INFO("Angular2: %d", motorCmdVel.angular2);

  motorCmdVel.dir1 = motorCmdVel.angular1 >= 0 ? 0 : 1;
  motorCmdVel.dir2 = motorCmdVel.angular2 >= 0 ? 0 : 1;

  topicPuber0.publish(motorCmdVel);
}
