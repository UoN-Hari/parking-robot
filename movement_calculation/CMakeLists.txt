cmake_minimum_required(VERSION 3.0.2)
project(movement_calculation)

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

catkin_package(
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}_node src/main.cpp src/subpuber.cpp)

target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES})
