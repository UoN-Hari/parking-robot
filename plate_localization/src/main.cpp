#include "plate_localization.h"

int main(int argc, char **argv)
{

  std::string projectName;
  // 获取模型路径
  ros::param::get("ProjectName", projectName);

  ros::init(argc, argv, projectName + "_node");

  // 使用一个类完成订阅 识别 发布
  SubPuber plateRecognizer;

  ros::spin();
  return 0;
}
