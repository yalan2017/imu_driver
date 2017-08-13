#include "imu_driver/teleop_key.h"

Teleop_Key::Teleop_Key()
{
    memset(js_axes, 0, sizeof(js_axes));
    memset(js_buttons, 0, sizeof(js_buttons));

    key_pub = nh.advertise<imu_driver::Control>("key_info", 5);
    sub_js = nh.subscribe("joy",1,&Teleop_Key::joyStick_callback,this);
    sub_mode = nh.subscribe("mode",1,&Teleop_Key::mode_callback,this);

    key_status = 0;
    kfd = 0;

    Mode = 2;  //远程控制：0:待机模式 1：自动模式 2：遥控模式

    stopFlag = false;
    steerModel = 0; //转向模式 0：前轮转向 1：四轮转向 2：原地转向
    gearModel = 1; //速度模式 0:后退 1:前进 2:加速档 3:最高速档
    controlSpeed  = 0;
    controlSteer  = 500;
    //
}

// void quit(int sig){
//   (void)sig;
//   tcsetattr(kfd, TCSANOW, &cooked);
//   ros::shutdown();
//   exit(0);
// }

void Teleop_Key::keyToControl(int key_status)
{
    //Model X on the joy stick!
    //按键A 前轮转向
    if(js_buttons[0]==1 && steerModel!=0){
      steerModel = 0;
      ROS_INFO("FRONT WHEEL STEERING!");
    }
    //按键B 四轮转向
    if(js_buttons[1]==1 && steerModel!=1){
      steerModel = 1;
      ROS_INFO("FOUR WHEEL STEERING!");
    }
    //按键X 原地转向
    if(js_buttons[2]==1 && steerModel!=2){
      steerModel = 2;
      ROS_INFO("STATIC TURN!");
    }
    // //按键Y
    // if(js_buttons[3]==1 && controlModel!=3){
    //   controlModel = 3;
    //   ROS_INFO("SPEED MANUAL! STEER AUTO!");
    // }

    //  go/stop and turn
    //start 前进
    if(js_buttons[7]==1 && gearModel!=1){
      gearModel = 1;
      ROS_INFO("NORMAL SPEED!");
    }
    //back 后退 
    if(js_buttons[6]==1 && gearModel!=0){
      gearModel = 0;
      ROS_INFO("BACK!");
    }
    //按键Y 加速
    if(js_buttons[3]==1 && gearModel!=2){
      gearModel = 3;
      ROS_INFO("ACCELERATE!");
    }

    //使能关，按键RB
    if(js_buttons[5] && !stopFlag) {
        ROS_INFO("DRIVER DISABLED!");
        stopFlag = true;//右键停
    }
    //动作使能开.按键LB
    if(js_buttons[4] && stopFlag){//LB
        ROS_INFO("DRIVER ENABLED!");
        stopFlag = false; //左键行
    } 


    //动作使能开
    if(!stopFlag){
          //转向，摇杆B 归一化
        controlSteer = int(500 - js_axes[3]*500);
          //速度，摇杆A 
        controlSpeed = int(abs(js_axes[1]*1000));
    }//动作使能 开 部分结束
    
    //动作使能关
    else {
        controlSteer = 500;
        controlSpeed = 0;
        control_msg.steerMode = 0;
        control_msg.gearMode = 1;
    }//动作使能 关 部分结束

  //ROS_INFO("%.2f\t%i", (float)vehicleCtrInfo.average_velocity, (int)vehicleCtrInfo.indexNum);
}

void Teleop_Key::switchMode()
{
    switch (Mode){
	//待机
    	case 0:
	     control_msg.Speed = 0;
    	     control_msg.Steer = 500;
   	     control_msg.steerMode = 0;
   	     control_msg.gearMode = 1;
	//自动	
	case 1:
	     control_msg.Speed = 0;
    	     control_msg.Steer = 500;
   	     control_msg.steerMode = 0;
   	     control_msg.gearMode = 1;	
	//遥控
	case 2:
	     control_msg.Speed = controlSpeed;
   	     control_msg.Steer = controlSteer;
    	     control_msg.steerMode = steerModel;
             control_msg.gearMode = gearModel;
    }
    key_pub.publish(control_msg); 
    
}

void Teleop_Key::keyLoop()
{
  char c;
  bool dirty=false;

  // get the console in raw mode                                                              
  tcgetattr(kfd, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  // Setting a new line, then end of file                         
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(kfd, TCSANOW, &raw);

  //for(;;)
  {
    // get the next event from the keyboard  
    if(read(kfd, &c, 1) < 0){
      perror("read():");
      exit(-1);
    }

    ROS_DEBUG("value: 0x%02X\n", c);
  
    switch(c){
        case KEYCODE_L:
            ROS_DEBUG("LEFT");
            key_status = 1;
            dirty = true;
            break;
        case KEYCODE_R:
            ROS_DEBUG("RIGHT");
            key_status = 2;
            dirty = true;
            break;
        case KEYCODE_U:
            ROS_DEBUG("UP");
            key_status = 3;
            dirty = true;
            break;
        case KEYCODE_D:
            ROS_DEBUG("DOWN");
            key_status = 4;
            dirty = true;
            break;
        case KEYCODE_Q:
            ROS_DEBUG("KEYCODE_Q");
            key_status = 5;
            dirty = true;
            break;
    }

    if(dirty ==true){
      keyToControl(key_status);
      key_pub.publish(control_msg);    
      dirty=false;
    }
  }
  return;
}

//手柄控制回调函数
void Teleop_Key::joyStick_callback(const sensor_msgs::Joy &msg)
{
  for (int i = 0; i < 8; i++){
    js_axes[i] = msg.axes[i];
  } 
  for (int i = 0; i < 11; i++){
    js_buttons[i] = msg.buttons[i];
  }
}

//模式接受函数
void Teleop_Key::mode_callback(const std_msgs::Int8::ConstPtr& mode_msg)
{
    Mode = int(mode_msg->data);
    ROS_INFO("MODE:%d",Mode);
}



int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_key");
  Teleop_Key teleop_turtle;

  control_msg.Speed = 0;
  control_msg.Steer = 500;
  control_msg.steerMode = 0;
  control_msg.gearMode = 1;

  //signal(SIGINT,quit);
  ros::Rate loop_rate(100);
  while (ros::ok()){
    //teleop_turtle.keyLoop();
    teleop_turtle.keyToControl(5);
    teleop_turtle.switchMode();
    ros::spinOnce(); 
    loop_rate.sleep();  
  }
  
  return(0);
}
