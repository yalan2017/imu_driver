#include <ros/ros.h>
#include <cereal_port/CerealPort.h>
// #include "imu_driver/JY901_frame.h"
#include "imu_driver/JY901.h"
#include "sensor_msgs/Imu.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Int8MultiArray.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/Float64MultiArray.h"




cereal::CerealPort serial_port;
ros::Publisher imu_pub;



CJY901 ::CJY901 ()
{
}

void CJY901 ::CopeSerialData(char ucData[],unsigned short usLength)
{
	static unsigned char chrTemp[2000];
	static unsigned char ucRxCnt = 0;	
	static unsigned short usRxLength = 0;


    memcpy(chrTemp,ucData,usLength);
	usRxLength += usLength;
    while (usRxLength >= 11)
    {
        if (chrTemp[0] != 0x55)
        {
			usRxLength--;
			memcpy(&chrTemp[0],&chrTemp[1],usRxLength);                        
            continue;
        }
		switch(chrTemp[1])
		{
			case 0x50:	memcpy(&stcTime,&chrTemp[2],8);break;
			case 0x51:	memcpy(&stcAcc,&chrTemp[2],8);break;
			case 0x52:	memcpy(&stcGyro,&chrTemp[2],8);break;
			case 0x53:	memcpy(&stcAngle,&chrTemp[2],8);break;
			case 0x54:	memcpy(&stcMag,&chrTemp[2],8);break;
			case 0x55:	memcpy(&stcDStatus,&chrTemp[2],8);break;
			case 0x56:	memcpy(&stcPress,&chrTemp[2],8);break;
			case 0x57:	memcpy(&stcLonLat,&chrTemp[2],8);break;
			case 0x58:	memcpy(&stcGPSV,&chrTemp[2],8);break;
		}
		usRxLength -= 11;
		memcpy(&chrTemp[0],&chrTemp[11],usRxLength);                     
    }
}
CJY901 JY901 = CJY901();



void *rcvThread(void *arg)
{
	unsigned char ucComNo[2] ={0,0};
	char chrBuffer[2000];
	unsigned short usLength=0,usCnt=0;
	unsigned long ulBaund=9600,ulComNo=3;
	while(1){
		// ROS_INFO("1");
		usLength = serial_port.read(chrBuffer,2000,1);
		//usLength = CollectUARTData(ulComNo,chrBuffer);
		if (usLength>0)
		{
			JY901.CopeSerialData(chrBuffer,usLength);
		}
		ros::Duration(0.01).sleep();
		
		if (usCnt++>=0)
		{
			// ROS_INFO("2");
			usCnt=0;
			// converting imu data to sensor_msgs::Imu, reference link below
			// https://gist.github.com/ShikherVerma/1b6ad5144688ed774835
		     sensor_msgs::Imu imu_msg = sensor_msgs::Imu();
		     imu_msg.header.stamp = ros::Time::now();
		     imu_msg.header.frame_id = "imu_link";

	            imu_msg.orientation.x = (float)JY901.stcAngle.Angle[0]/32768*180;//(float)JY901.stcGyro.w[0]/32768*2000;    //?????
		    imu_msg.orientation.y = (float)JY901.stcAngle.Angle[1]/32768*180;//(float)JY901.stcGyro.w[1]/32768*2000;	//?????
		    imu_msg.orientation.z = (float)JY901.stcAngle.Angle[2]/32768*180;//(float)JY901.stcGyro.w[2]/32768*2000;	//?????
		    imu_msg.orientation.w = 0.0;
		    //imu_msg.angular_velocity_covariance = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
		    imu_msg.angular_velocity.x = (float)JY901.stcGyro.w[0]/32768*2000;//(float)JY901.stcAngle.Angle[0]/32768*180;	//?????
		    imu_msg.angular_velocity.y = (float)JY901.stcGyro.w[1]/32768*2000;//(float)JY901.stcAngle.Angle[1]/32768*180;	//?????
		    imu_msg.angular_velocity.z = (float)JY901.stcGyro.w[2]/32768*2000;//(float)JY901.stcAngle.Angle[2]/32768*180;	//?????
		    //imu_msg.angular_velocity_covariance = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
		    imu_msg.linear_acceleration.x = (float)JY901.stcAcc.a[0]/32768*16;
		    imu_msg.linear_acceleration.y = (float)JY901.stcAcc.a[1]/32768*16;
		    imu_msg.linear_acceleration.z = (float)JY901.stcAcc.a[2]/32768*16;
		    //imu_msg.angular_velocity_covariance = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
		    imu_pub.publish(imu_msg);
                    ROS_INFO("IMU SENDIND DATA");
                    ros::Duration(0.1).sleep();//
    

		}	


	}	
}



int main(int argc, char** argv)
{

    ros::init(argc, argv, "imu_node");  
    std::string portname;
    int baudrate;
    ros::NodeHandle pn("~");
    ros::NodeHandle nh;
    imu_pub = nh.advertise<sensor_msgs::Imu>("imu/data", 10);
    pn.param<std::string>("port", portname, "/dev/ttyUSB0");//ttyUSB1
    pn.param("baudrate", baudrate, 115200);
   // ros::Duration(0.1).sleep();//
    
    try{ serial_port.open((char*)portname.c_str(), baudrate); }
    catch(cereal::Exception& e)
    {
        ROS_INFO("unable to open imu com");
    }      

	
    //Create receive thread
    pthread_t rcvThrID;   //receive thread ID
    int err;
    err = pthread_create(&rcvThrID, NULL, rcvThread, NULL);
    if (err != 0) 
    {
	ROS_ERROR("unable to create receive thread");
	return -1;
    }
	
    ros::spin();
    return 0;

}



