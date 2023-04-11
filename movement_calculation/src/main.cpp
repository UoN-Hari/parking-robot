#include "subpuber.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "movement_calculation_node");
  SubPuber subPuber;
  ros::spin();
  return 0;
}
