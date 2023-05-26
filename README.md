## Install
```bash
$ mkdir catkin_ws
$ cd catkin_ws/
$ git clone git@github.com:UoN-Hari/parking-robot.git src
$ catkin_make
```
## Run

```bash

# Open camera. Serial port needed
roslaunch realsense2_camera rs_camera.launch 

# Open plate recognization.
# /recognition_result is the result 
# https://github.com/BSSNBSSN/HyperLPR-ROS/blob/master/Prj-ROS/README.md
roslaunch hyperlpr bringup.launch

# Open mcu node. Serial port needed
roslaunch mcu_serial serial.launch

# Open cmd_vel pub node
roslaunch motion_control bringup.launch

# Open cmd_vel to motor spd calculation node.
roslaunch movement_calculation bringup.launch

```