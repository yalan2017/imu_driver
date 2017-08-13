#include <ros/ros.h>
#include <cereal_port/CerealPort.h>
#include "imu_driver/JY901_frame.h"
#include "imu_driver/JY901.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Int8MultiArray.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/Float64MultiArray.h"

//void *rcvThread(void *arg)
//{
//	char chrBuffer[200];
//        unsigned char chrTemp[200];	
//	serial_port.readBytes(chrBuffer,11,1000);
//	memcpy(chrTemp,chrBuffer,11);
//	if(chrTemp[0]!=0x55) ROS_INFO("%x",chrTemp);
//        else
//		ROS_INFO("%x",chrTemp);
//}

ros::Publisher gyro_pub;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "mti_node");    
    ros::NodeHandle pn("~");
    ros::NodeHandle nh;
    gyro_pub = nh.advertise<imu_driver::JY901_frame>("Gyro", 30);

    cereal::CerealPort serial_port;

    imu_driver::JY901_frame imu_msg;
    //CJY901 JY901;
    // Params
    std::string portname;
    int baudrate;
    pn.param<std::string>("port", portname, "/dev/ttyUSB0");
    pn.param("baudrate", baudrate, 115200);
    char chrBuffer[200];
    unsigned char chrTemp[200];
    try{ serial_port.open((char*)portname.c_str(), baudrate); }
    catch(cereal::Exception& e)
    {
        ROS_INFO("%i",baudrate);
    }

    struct STime		stcTime;
    struct SAcc 		stcAcc;
    struct SGyro 		stcGyro;
    struct SAngle 		stcAngle;
    struct SMag 		stcMag;
    struct SDStatus 		stcDStatus;
    struct SPress 		stcPress;
    struct SLonLat 		stcLonLat;
    struct SGPSV 		stcGPSV; 


   // ros::Rate r(100);

    while(ros::ok())
    {
//        
//      //  ROS_INFO("%i",baudrate);
	serial_port.readBytes(chrBuffer,11,1000);
	memcpy(chrTemp,chrBuffer,11);
	if(chrTemp[0]!=0x55) ROS_INFO("%i",baudrate);
        else{
		//ROS_INFO("%x\t%x\t%x\t%x\t%x\t%x\t%x\t%x",chrTemp[1],chrTemp[2],chrTemp[3],chrTemp[4],chrTemp[5],chrTemp[6],chrTemp[7],chrTemp[8]);
		switch(chrTemp[1])
		{
			case 0x50: 	stcTime.ucYear = chrTemp[2];
					stcTime.ucMonth = chrTemp[3];
					stcTime.ucDay 	= chrTemp[4];
					stcTime.ucHour 	= chrTemp[5];
					stcTime.ucMinute = chrTemp[6];
					stcTime.ucSecond = chrTemp[7];
					stcTime.usMiliSecond=((unsigned short)chrTemp[9]<<8)|chrTemp[8];
					break;
			case 0x51:	stcAcc.a[0] = ((unsigned short)chrTemp[3]<<8)|chrTemp[2];
					stcAcc.a[1] = ((unsigned short)chrTemp[5]<<8)|chrTemp[4];
					stcAcc.a[2] = ((unsigned short)chrTemp[7]<<8)|chrTemp[6];
					break;
			case 0x52:	stcGyro.w[0] = ((unsigned short)chrTemp[3]<<8)|chrTemp[2];
					stcGyro.w[1] = ((unsigned short)chrTemp[5]<<8)|chrTemp[4];
					stcGyro.w[2] = ((unsigned short)chrTemp[7]<<8)|chrTemp[6];
					break;
			case 0x53:	stcAngle.Angle[0] = ((unsigned short)chrTemp[3]<<8)|chrTemp[2];
					stcAngle.Angle[1] = ((unsigned short)chrTemp[5]<<8)|chrTemp[4];
					stcAngle.Angle[2] = ((unsigned short)chrTemp[7]<<8)|chrTemp[6];
					stcAngle.T = ((unsigned short)chrTemp[9]<<8)|chrTemp[8];
					break;
			case 0x54:	stcMag.h[0] = ((unsigned short)chrTemp[3]<<8)|chrTemp[2];
					stcMag.h[1] = ((unsigned short)chrTemp[5]<<8)|chrTemp[4];
					stcMag.h[2] = ((unsigned short)chrTemp[7]<<8)|chrTemp[6];
					stcAngle.T = ((unsigned short)chrTemp[9]<<8)|chrTemp[8];
					break;
			case 0x55:	stcDStatus.sDStatus[0] = ((unsigned short)chrTemp[3]<<8)|chrTemp[2];
					stcDStatus.sDStatus[1] = ((unsigned short)chrTemp[5]<<8)|chrTemp[4];
					stcDStatus.sDStatus[2] = ((unsigned short)chrTemp[7]<<8)|chrTemp[6];
					stcDStatus.sDStatus[3] = ((unsigned short)chrTemp[9]<<8)|chrTemp[8];
					break;
//			case 0x56:	chrTemp[2] = 0x12;chrTemp[3] = 0x34;chrTemp[4] = 0x56;chrTemp[5] = 0x78;
//					CharToLong((char*)&stcPress.lPressure,(char*)&chrTemp[2]);
//					CharToLong((char*)&stcPress.lAltitude,(char*)&chrTemp[6]);
//					
//					break;
			case 0x57:	stcLonLat.lLon = ((unsigned short)chrTemp[5]<<24)|((unsigned short)chrTemp[4]<<16)|((unsigned short)chrTemp[3]<<8)|chrTemp[2];
					stcLonLat.lLat = ((unsigned short)chrTemp[9]<<24)|((unsigned short)chrTemp[8]<<16)|((unsigned short)chrTemp[7]<<8)|chrTemp[6];
					break;
			case 0x58:	stcGPSV.sGPSHeight = ((unsigned short)chrTemp[3]<<8)|chrTemp[2];
					stcGPSV.sGPSYaw = ((unsigned short)chrTemp[5]<<8)|chrTemp[4];
					CharToLong((char*)&stcGPSV.lGPSVelocity,(char*)&chrTemp[6]);
					break;
		}
	}
	
	  imu_msg.gyro_x = (float)stcGyro.w[0]/32768*2000;
	imu_msg.gyro_y = (float)stcGyro.w[1]/32768*2000;
	imu_msg.gyro_z = (float)stcGyro.w[2]/32768*2000;

	imu_msg.acc_x = (float)stcAcc.a[0]/32768*16;
	imu_msg.acc_y = (float)stcAcc.a[1]/32768*16;
	imu_msg.acc_z = (float)stcAcc.a[2]/32768*16;

	imu_msg.angle_x = (float)stcAngle.Angle[0]/32768*180;
	imu_msg.angle_y = (float)stcAngle.Angle[1]/32768*180;
	imu_msg.angle_z = (float)stcAngle.Angle[2]/32768*180;

	imu_msg.latitute = (double)stcLonLat.lLon/10000000;
	imu_msg.longtitute = (double)stcLonLat.lLat/10000000;

	gyro_pub.publish(imu_msg);
        ros::spinOnce();
       // r.sleep();


//ros::Rate loop_rate(2);

ros::Duration(0.013).sleep();
  }

    return(0);
}

