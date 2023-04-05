import rospy
# from geometry_msgs.msg import Twist
# from roborts_msgs.msg import GimbalAngle
from mcu_serial.msg import motor_msgs


class Listener:
    # left_twist_msg = Twist()
    # right_twist_msg = Twist()
    # gimbal_cmd_msg = GimbalAngle()
    # gimbal_twist_msg = Twist()
    motor_msg = motor_msgs()

    def __init__(self) -> None:
        pass

    def motor_callback(self, data):
        self.motor_msg = data

        # rospy.loginfo(rospy.get_caller_id() + "\nleft_cmd_vel msg: %s", self.twist_msg)

    
    def create_subscriber(self):
        rospy.Subscriber('/motor_cmd', motor_msgs, self.motor_callback, queue_size=10, tcp_nodelay=True)
        
