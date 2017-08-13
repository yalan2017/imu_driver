#include <ros/ros.h>
#include <cereal_port/CerealPort.h>

#include "imu_driver/JY901_frame.h"
#include "imu_driver/JY901.h"
#include "imu_driver/Mile.h"
#include "imu_driver/Control.h"

#include "std_msgs/Float64.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Int8MultiArray.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/Float64MultiArray.h"


imu_driver::Mile mile_msg;
imu_driver::Control Control_msg;
ros::Publisher mile_pub;
ros::Subscriber control_sub;
cereal::CerealPort serial_port;
bool read_flag;
bool write_flag;
char chrBuffer[200];
unsigned char chrTemp[200];

void readSerial(){
    try{serial_port.readBytes(chrBuffer,11,1000);}
    catch(cereal::TimeoutException& e)
    {
        readSerial();
    }
}

void *rcvThread(void *arg)
{
	while(1){
            readSerial();
            memcpy(chrTemp,chrBuffer,11);
            if(chrTemp[0]!=0x55){
                ros::Duration(0.001).sleep();
                ROS_INFO("can not find start");
                if(!serial_port.flush()) ROS_INFO("flush failed!");
            }
            else{
                switch(chrTemp[1])
                {
                    //receive
                    case 0x41:  mile_msg.leftPulse = ((unsigned short)chrTemp[5]<<24)|((unsigned short)chrTemp[4]<<16)|((unsigned short)chrTemp[3]<<8)|chrTemp[2];
                                mile_msg.rightPulse = ((unsigned short)chrTemp[9]<<24)|((unsigned short)chrTemp[8]<<16)|((unsigned short)chrTemp[7]<<8)|chrTemp[6];
                                // ROS_INFO("pulse %i %i",mile_msg.leftPulse, mile_msg.rightPulse);
                                break;
                }
            }
            mile_pub.publish(mile_msg);//------------如果需要离线看效果就注释这句

            //send 
            chrBuffer[0] = 0x55;
            chrBuffer[1] = 0x31;
            chrBuffer[2] = (char)(Control_msg.Speed>>8);
            chrBuffer[3] = (char)(Control_msg.Speed & 0x00ff);
            chrBuffer[4] = (char)(Control_msg.Steer>>8);
            chrBuffer[5] = (char)(Control_msg.Steer & 0x00ff);
            chrBuffer[6] = (char)(Control_msg.steerMode);
            chrBuffer[7] = (char)(Control_msg.gearMode);
            chrBuffer[8] = 0x00;
            chrBuffer[9] = 0x00;
            chrBuffer[10] = 0x00;
            for(int i=2; i<10; i++)
            {
                 chrBuffer[10] = chrBuffer[10] + chrBuffer[i];
            }
            serial_port.write(chrBuffer, 11);
	}
}

void keyMsgCallback(imu_driver::Control key_msg)
{
    Control_msg.Speed = key_msg.Speed;
    Control_msg.Steer = key_msg.Steer;
    Control_msg.steerMode = key_msg.steerMode;
    Control_msg.gearMode = key_msg.gearMode;
   // ROS_INFO("keyinfo%d\n",Control_msg.Speed);
} 



int main(int argc, char** argv)
{
    ros::init(argc, argv, "zigbee_node");    
    ros::NodeHandle pn("~");
    ros::NodeHandle nh;
    mile_pub = nh.advertise<imu_driver::Mile>("Pulse", 30);//------------如果需要离线看效果就注释这句
    control_sub = nh.subscribe("key_info", 10, keyMsgCallback);
    read_flag = true;
    write_flag = false;

    std::string portname;
    int baudrate;
    pn.param<std::string>("port", portname, "/dev/ttyUSB1");//ttyUSB0,serial port, communication
    pn.param("baudrate", baudrate, 115200);
    char chrBuffer[200];
    unsigned char chrTemp[200];
    try{ 
        serial_port.open((char*)portname.c_str(), baudrate); 
    }
    catch(cereal::Exception& e){
        ROS_INFO("unable to open zigbee com");
    }

    //Create receive thread
    pthread_t rcvThrID;   //receive thread ID
    int err;
    err = pthread_create(&rcvThrID, NULL, rcvThread, NULL);
    if (err != 0) {
	   ROS_ERROR("unable to create receive thread");
	   return -1;
    }
	
    ros::spin();
    return 0;
}
