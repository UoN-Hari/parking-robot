#include "subpuber.h"

// #define SQUARE
#define MOTOR_OFFSET
// #define ANGULAR_OFFSET

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
  geometry_msgs::Pose2D curPose;

#ifdef SQUARE
  // Square
  // while(1) {
  // for(int i = 0; i <= 3; i++) {
    startTime =ros::Time::now().toSec();

    topicPuber0.publish(linearCmdVel);
    while((ros::Time::now().toSec() - startTime - lengthTimeOffset) < lengthTime) {
      topicPuber0.publish(linearCmdVel);
    }
    angularCmdVel.linear.x = 0;
    topicPuber0.publish(linearCmdVel);
    lengthTimeOffset = ros::Time::now().toSec() - startTime - lengthTimeOffset - lengthTime;
    // ROS_INFO("LengthTimeOffset: %lf", lengthTimeOffset);

    startTime =ros::Time::now().toSec();
    while(ros::Time::now().toSec() - startTime < angularTime) {
      topicPuber0.publish(angularCmdVel);
    }
    angularCmdVel.angular.z = 0;
    topicPuber0.publish(angularCmdVel);
    angularTimeOffset = ros::Time::now().toSec() - startTime + angularTimeOffset - angularTime;
    // startTime =ros::Time::now().toSec();
    // topicPuber0.publish(angularCmdVel);
    // while((ros::Time::now().toSec() - startTime + angularTimeOffset) < angularTime) {}
    // angularTimeOffset = ros::Time::now().toSec() - startTime + angularTimeOffset - angularTime;
    // ROS_INFO("AngularTimeOffset: %lf", angularTimeOffset);
  // }
#endif

#ifdef MOTOR_OFFSET 
  // MotorOffset identification
  startTime =ros::Time::now().toSec();
  while(ros::Time::now().toSec() - startTime < lengthTime) {
    // std::cout<<"hahahah"<<std::endl;
    topicPuber0.publish(linearCmdVel);
    curPose.x = (ros::Time::now().toSec() - startTime) * linearCmdVel.linear.x;
    topicPuber1.publish(curPose);
  }
  linearCmdVel.linear.x = 0;
  topicPuber0.publish(linearCmdVel);
  lengthTimeOffset = ros::Time::now().toSec() - startTime - lengthTimeOffset - lengthTime;
  ROS_INFO("LengthTimeOffset: %lf", lengthTimeOffset);
#endif

#ifdef ANGULAR_OFFSET
  // AngularOffset identification
  startTime =ros::Time::now().toSec();
  // Turn for 1 cycle
  while(ros::Time::now().toSec() - startTime < angularTime * 4) {
    topicPuber0.publish(angularCmdVel);
  }
  angularCmdVel.angular.z = 0;
  topicPuber0.publish(angularCmdVel);
  angularTimeOffset = ros::Time::now().toSec() - startTime + angularTimeOffset - angularTime;
  ROS_INFO("AngularTimeOffset: %lf", angularTimeOffset);
#endif

}
