#include "subpuber.h"

void SubPuber::MovementCalculationCallback(const geometry_msgs::Twist &cmdVel)
{
  mcu_serial::motor_msgs motorCmdVel;
  double angularL = motorOffset * (cmdVel.linear.x - cmdVel.angular.z);
  double angularR = motorOffset * (cmdVel.linear.x + cmdVel.angular.z);

  if(angularL - (int)angularL != 0 ||
     angularR - (int)angularR != 0 ) {
      ros::Exception("MOTOR SPEED NOT INT!!!!!!!!!!!!!!");
  }

  motorCmdVel.angular2 = angularL;
  motorCmdVel.angular1 = angularR;

  // Right wheel offset ratio refers to Left wheel
  motorCmdVel.angular2 *= lrOffset;

  motorCmdVel.dir1 = motorCmdVel.angular1 >= 0 ? 1 : 0;
  motorCmdVel.dir2 = motorCmdVel.angular2 >= 0 ? 1 : 0;

  topicPuber0.publish(motorCmdVel);
}
