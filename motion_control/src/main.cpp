#include "subpuber.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "motion_control_node");
  SubPuber subPuber;
  subPuber.MotionControlCallBack();
  return 0;
}
