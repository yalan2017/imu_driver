#ifndef TELEOP_KEY_H
#define TELEOP_KEY_H

#define KEYCODE_R 0x43 
#define KEYCODE_L 0x44
#define KEYCODE_U 0x41
#define KEYCODE_D 0x42
#define KEYCODE_Q 0x71

#include <ros/ros.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include "std_msgs/Int32.h"
#include "std_msgs/Int8.h"
#include <sensor_msgs/Joy.h>    //joy stick msg
#include "imu_driver/Control.h"
#include "imu_driver/controlConvert.h"
#include "std_msgs/Float64MultiArray.h"

imu_driver::Control control_msg;  

class Teleop_Key
{
public:
  Teleop_Key();
	void keyLoop();
  void quit(int sig);
  void keyToControl(int key_status);
  void switchMode();

  void joyStick_callback(const sensor_msgs::Joy &msg);//摇杆控制
  void mode_callback(const std_msgs::Int8::ConstPtr& mode_msg);

  float js_axes[8];
  int js_buttons[11];

  bool stopFlag;

  int Mode; //控制模式
  int kfd;  
  struct termios cooked, raw;
  int gearModel, steerModel;
  int controlSpeed, controlSteer;

  unsigned int controlModel; //0:manual; 1:automatic
  unsigned int turnModel; //0:goAndTurn; 1:stopAndTrun;

private:
  ros::NodeHandle nh;
  ros::Publisher key_pub;
  ros::Subscriber sub_js; //joy stick sub
  ros::Subscriber sub_mode; //mode sub
  

  int key_status;
};

#endif

