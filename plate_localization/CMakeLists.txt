cmake_minimum_required(VERSION 3.0.2)
project(plate_localization)

find_package(OpenCV REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  cmake_modules
  roscpp
  rospy
  cv_bridge
  std_msgs
  image_transport
  sensor_msgs
  geometry_msgs
)

catkin_package(
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)


add_executable(${PROJECT_NAME}_node src/${PROJECT_NAME}_node.cpp src/main.cpp)

target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
  ${OpenCV_LIBS}
)
