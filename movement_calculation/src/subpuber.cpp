#include "subpuber.h"

void SubPuber::MovementCalculationCallback(const geometry_msgs::Twist &cmdVel)
{
  mcu_serial::motor_msgs motorCmdVel;
  motorCmdVel.angular1 = cmdVel.linear.x - cmdVel.angular.z;
  motorCmdVel.angular2 = cmdVel.linear.x + cmdVel.angular.z;
  // Right wheel offset ratio refers to Left wheel
  motorCmdVel.angular2 *= lrOffset;
  // Motor offset from motor cmd to unit
  motorCmdVel.angular1 *= motorOffset;
  motorCmdVel.angular2 *= motorOffset;

  motorCmdVel.dir1 = motorCmdVel.angular1 > 0 ? 0 : 1;
  motorCmdVel.dir2 = motorCmdVel.angular2 > 0 ? 0 : 1;

  topicPuber0.publish(motorCmdVel);
}
