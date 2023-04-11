cmake_minimum_required(VERSION 3.0.2)
project(motion_control)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  sensor_msgs
  geometry_msgs
  nav_msgs
  tf
  tf2
  cv_bridge
  image_transport
  mcu_serial
)

add_message_files(
  FILES
  motor_msgs.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS message_runtime
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}_node src/main.cpp src/subpuber.cpp)

target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES})
