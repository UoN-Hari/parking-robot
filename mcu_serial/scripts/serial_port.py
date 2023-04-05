from io import BytesIO
import serial
from geometry_msgs.msg import Twist
import sys

class McuSerial:
    rc_msg = Twist()
    def __init__(self) -> None:
        self.serial = serial.Serial()

    def OpenPort(self):
        self.serial.port = "/dev/ttyUSB0"
        self.serial.baudrate = 921600
        self.serial.bytesize = 8
        self.serial.stopbits = 1
        self.serial.parity = "N"
        self.serial.timeout = 5
        self.serial.open()

    def ClosePort(self):
        self.serial.close()

    def Transmit(self, data):
        if(self.serial.isOpen()):
            self.serial.write(data)
        else:
            print('Sending message failed, please check your connection')

    def TransmitRosMsg(self, ros_msg):
        temp_bytes = BytesIO()

        temp_bytes.seek(0)
        ros_msg.serialize(temp_bytes)
        temp_bytes.seek(0)

        
        self.Transmit(temp_bytes.read())

    def receiveMsg(self):
        if(self.serial.isOpen()):
            buffer = self.serial.read(48)
            self.rc_msg.deserialize(buffer)