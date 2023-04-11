#include "subpuber.h"

void SubPuber::MotionControlCallBack()
{
  geometry_msgs::Twist cmdVel;
  double secs =ros::Time::now().toSec()
  
  for (int i = 0; i <= 1; i++) {
    topicPuber0.publish(cmdVel);
  }
}
