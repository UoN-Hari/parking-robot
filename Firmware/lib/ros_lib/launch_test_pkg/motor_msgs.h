#ifndef _ROS_launch_test_pkg_motor_msgs_h
#define _ROS_launch_test_pkg_motor_msgs_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace launch_test_pkg
{

  class motor_msgs : public ros::Msg
  {
    public:
      typedef int16_t _angular1_type;
      _angular1_type angular1;
      typedef int16_t _angular2_type;
      _angular2_type angular2;
      typedef int8_t _dir1_type;
      _dir1_type dir1;
      typedef int8_t _dir2_type;
      _dir2_type dir2;

    motor_msgs():
      angular1(0),
      angular2(0),
      dir1(0),
      dir2(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_angular1;
      u_angular1.real = this->angular1;
      *(outbuffer + offset + 0) = (u_angular1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angular1.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->angular1);
      union {
        int16_t real;
        uint16_t base;
      } u_angular2;
      u_angular2.real = this->angular2;
      *(outbuffer + offset + 0) = (u_angular2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angular2.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->angular2);
      union {
        int8_t real;
        uint8_t base;
      } u_dir1;
      u_dir1.real = this->dir1;
      *(outbuffer + offset + 0) = (u_dir1.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->dir1);
      union {
        int8_t real;
        uint8_t base;
      } u_dir2;
      u_dir2.real = this->dir2;
      *(outbuffer + offset + 0) = (u_dir2.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->dir2);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_angular1;
      u_angular1.base = 0;
      u_angular1.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angular1.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->angular1 = u_angular1.real;
      offset += sizeof(this->angular1);
      union {
        int16_t real;
        uint16_t base;
      } u_angular2;
      u_angular2.base = 0;
      u_angular2.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angular2.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->angular2 = u_angular2.real;
      offset += sizeof(this->angular2);
      union {
        int8_t real;
        uint8_t base;
      } u_dir1;
      u_dir1.base = 0;
      u_dir1.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->dir1 = u_dir1.real;
      offset += sizeof(this->dir1);
      union {
        int8_t real;
        uint8_t base;
      } u_dir2;
      u_dir2.base = 0;
      u_dir2.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->dir2 = u_dir2.real;
      offset += sizeof(this->dir2);
     return offset;
    }

    virtual const char * getType() override { return "launch_test_pkg/motor_msgs"; };
    virtual const char * getMD5() override { return "8a4c0d0ea0c11be5460ca4012f5d0ab2"; };

  };

}
#endif
