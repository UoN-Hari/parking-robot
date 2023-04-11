#include "subpuber.h"

void SubPuber::MotionControlCallBack()
{
  double lastLength, lastWidth;
  double lengthTimeOffset = 0, widthTimeOffset = 0, angularTimeOffset = 0;
  const double lengthTime = rectLength / linearSpd;
  const double widthTime = rectWidth / linearSpd;
  const double angularTime = M_PI_2 / angularSpd;
  double startTime;

  geometry_msgs::Twist linearCmdVel;
  linearCmdVel.linear.x = linearSpd;
  geometry_msgs::Twist angularCmdVel;
  angularCmdVel.angular.z = angularSpd;
  while(1) {
  // for(int i = 0; i <= 3; i++) {
    startTime =ros::Time::now().toSec();
    topicPuber0.publish(linearCmdVel);
    while((ros::Time::now().toSec() - startTime - lengthTimeOffset) < lengthTime) {}
    lengthTimeOffset = ros::Time::now().toSec() - startTime - lengthTimeOffset - lengthTime;
    ROS_INFO("LengthTimeOffset: %lf", lengthTimeOffset);

    startTime =ros::Time::now().toSec();
    topicPuber0.publish(angularCmdVel);
    while((ros::Time::now().toSec() - startTime + angularTimeOffset) < angularTime) {}
    angularTimeOffset = ros::Time::now().toSec() - startTime + angularTimeOffset - angularTime;
    ROS_INFO("AngularTimeOffset: %lf", angularTimeOffset);
  }
}
