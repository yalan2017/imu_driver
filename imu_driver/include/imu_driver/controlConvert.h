#ifndef CONTROLCONVERT_H
#define CONTROLCONVERT_H
#include <math.h>

#define PI					3.1415926	

#define WHEELTRACK			0.5		//轮距
#define WHEELBASE			0.8		//轴距
#define MAX_INCREASE_ANGLE	1.8		//控制周期最大转角范围每秒36度
#define MAX_INCREASE_SPEED	2		//制周期最大速度增量  

#define MAX_LEFT_ANGLE		30		//左侧轮最大转角
#define MAX_RIGHT_ANGLE		25		//右侧轮最大转角
#define MIN_LEFT_ANGLE		-25		//左侧轮最小转角
#define MIN_RIGHT_ANGLE		-30		//右侧轮最小转角
#define MAX_VELOCITY		2.5		//最大轮速 20km/h
#define MIN_VELOCITY		-2		//最大轮速 20km/h
#define MAX_RADIUS			100000		//最大轮速  

double TURN_IN[193] = {-24,-23.75,-23.5,-23.25,-23,-22.75,-22.5,-22.25,-22,-21.75,-21.5,-21.25,-21,-20.75,-20.5,-20.25,-20,-19.75,-19.5,-19.25,-19,-18.75,-18.5,-18.25,-18,-17.75,-17.5,-17.25,-17,-16.75,-16.5,-16.25,-16,-15.75,-15.5,-15.25,-15,-14.75,-14.5,-14.25,-14,-13.75,-13.5,-13.25,-13,-12.75,-12.5,-12.25,-12,-11.75,-11.5,-11.25,-11,-10.75,-10.5,-10.25,-10,-9.75,-9.5,-9.25,-9,-8.75,-8.5,-8.25,-8,-7.75,-7.5,-7.25,-7,-6.75,-6.5,-6.25,-6,-5.75,-5.5,-5.25,-5,-4.75,-4.5,-4.25,-4,-3.75,-3.5,-3.25,-3,-2.75,-2.5,-2.25,-2,-1.75,-1.5,-1.25,-1,-0.75,-0.5,-0.25,0,0.25,0.5,0.75,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.25,4.5,4.75,5,5.25,5.5,5.75,6,6.25,6.5,6.75,7,7.25,7.5,7.75,8,8.25,8.5,8.75,9,9.25,9.5,9.75,10,10.25,10.5,10.75,11,11.25,11.5,11.75,12,12.25,12.5,12.75,13,13.25,13.5,13.75,14,14.25,14.5,14.75,15,15.25,15.5,15.75,16,16.25,16.5,16.75,17,17.25,17.5,17.75,18,18.25,18.5,18.75,19,19.25,19.5,19.75,20,20.25,20.5,20.75,21,21.25,21.5,21.75,22,22.25,22.5,22.75,23,23.25,23.5,23.75,24};
// double TURN_LEFT[193] = {-19.565,-19.390,-19.213,-19.036,-18.859,-18.681,-18.503,-18.325,-18.146,-17.966,-17.786,-17.606,-17.425,-17.244,-17.062,-16.880,-16.697,-16.513,-16.330,-16.145,-15.961,-15.775,-15.589,-15.403,-15.216,-15.029,-14.841,-14.652,-14.463,-14.273,-14.083,-13.892,-13.701,-13.509,-13.316,-13.123,-12.930,-12.735,-12.540,-12.345,-12.149,-11.952,-11.755,-11.556,-11.358,-11.158,-10.959,-10.758,-10.557,-10.355,-10.152,-9.949,-9.745,-9.540,-9.335,-9.129,-8.922,-8.714,-8.506,-8.297,-8.087,-7.877,-7.666,-7.454,-7.241,-7.028,-6.813,-6.598,-6.383,-6.166,-5.949,-5.731,-5.512,-5.292,-5.071,-4.850,-4.628,-4.405,-4.181,-3.956,-3.730,-3.504,-3.277,-3.048,-2.819,-2.589,-2.359,-2.127,-1.894,-1.661,-1.426,-1.191,-0.955,-0.717,-0.479,-0.240,0.000,0.241,0.483,0.726,0.970,1.215,1.461,1.707,1.955,2.204,2.454,2.705,2.957,3.210,3.464,3.719,3.975,4.232,4.490,4.749,5.009,5.270,5.533,5.796,6.061,6.326,6.593,6.861,7.129,7.399,7.670,7.943,8.216,8.490,8.766,9.043,9.320,9.599,9.879,10.160,10.443,10.726,11.011,11.297,11.584,11.872,12.161,12.452,12.743,13.036,13.330,13.625,13.921,14.219,14.517,14.817,15.118,15.420,15.724,16.028,16.334,16.641,16.949,17.258,17.569,17.880,18.193,18.507,18.822,19.139,19.456,19.775,20.095,20.416,20.738,21.061,21.386,21.712,22.038,22.366,22.695,23.026,23.357,23.690,24.023,24.358,24.694,25.031,25.369,25.708,26.048,26.390,26.732,27.075,27.420,27.766,28.112};
// double TURN_RIGHT[193] = {-28.112,-27.766,-27.420,-27.075,-26.732,-26.390,-26.048,-25.708,-25.369,-25.031,-24.694,-24.358,-24.023,-23.690,-23.357,-23.026,-22.695,-22.366,-22.038,-21.712,-21.386,-21.061,-20.738,-20.416,-20.095,-19.775,-19.456,-19.139,-18.822,-18.507,-18.193,-17.880,-17.569,-17.258,-16.949,-16.641,-16.334,-16.028,-15.724,-15.420,-15.118,-14.817,-14.517,-14.219,-13.921,-13.625,-13.330,-13.036,-12.743,-12.452,-12.161,-11.872,-11.584,-11.297,-11.011,-10.726,-10.443,-10.160,-9.879,-9.599,-9.320,-9.043,-8.766,-8.490,-8.216,-7.943,-7.670,-7.399,-7.129,-6.861,-6.593,-6.326,-6.061,-5.796,-5.533,-5.270,-5.009,-4.749,-4.490,-4.232,-3.975,-3.719,-3.464,-3.210,-2.957,-2.705,-2.454,-2.204,-1.955,-1.707,-1.461,-1.215,-0.970,-0.726,-0.483,-0.241,0.000,0.240,0.479,0.717,0.955,1.191,1.426,1.661,1.894,2.127,2.359,2.589,2.819,3.048,3.277,3.504,3.730,3.956,4.181,4.405,4.628,4.850,5.071,5.292,5.512,5.731,5.949,6.166,6.383,6.598,6.813,7.028,7.241,7.454,7.666,7.877,8.087,8.297,8.506,8.714,8.922,9.129,9.335,9.540,9.745,9.949,10.152,10.355,10.557,10.758,10.959,11.158,11.358,11.556,11.755,11.952,12.149,12.345,12.540,12.735,12.930,13.123,13.316,13.509,13.701,13.892,14.083,14.273,14.463,14.652,14.841,15.029,15.216,15.403,15.589,15.775,15.961,16.145,16.330,16.513,16.697,16.880,17.062,17.244,17.425,17.606,17.786,17.966,18.146,18.325,18.503,18.681,18.859,19.036,19.213,19.390,19.565};
double LEFT_UP[193] = {-11.280,-11.172,-11.064,-10.956,-10.848,-10.740,-10.632,-10.524,-10.415,-10.307,-10.198,-10.090,-9.981,-9.872,-9.763,-9.653,-9.544,-9.435,-9.325,-9.215,-9.105,-8.995,-8.885,-8.775,-8.664,-8.553,-8.443,-8.332,-8.220,-8.109,-7.997,-7.886,-7.774,-7.661,-7.549,-7.436,-7.324,-7.211,-7.097,-6.984,-6.870,-6.756,-6.642,-6.528,-6.413,-6.298,-6.183,-6.068,-5.952,-5.836,-5.720,-5.604,-5.487,-5.370,-5.253,-5.135,-5.017,-4.899,-4.781,-4.662,-4.543,-4.424,-4.304,-4.184,-4.063,-3.943,-3.821,-3.700,-3.578,-3.456,-3.333,-3.210,-3.087,-2.964,-2.839,-2.715,-2.590,-2.465,-2.339,-2.213,-2.087,-1.960,-1.832,-1.704,-1.576,-1.448,-1.318,-1.189,-1.059,-0.928,-0.797,-0.665,-0.533,-0.401,-0.268,-0.134,0.000,0.135,0.270,0.406,0.542,0.679,0.816,0.954,1.093,1.232,1.371,1.512,1.653,1.794,1.937,2.079,2.223,2.367,2.512,2.657,2.803,2.950,3.098,3.246,3.395,3.545,3.695,3.846,3.998,4.151,4.304,4.458,4.613,4.769,4.926,5.083,5.241,5.400,5.560,5.721,5.883,6.045,6.208,6.373,6.538,6.704,6.871,7.039,7.208,7.378,7.549,7.721,7.894,8.068,8.243,8.419,8.597,8.775,8.954,9.135,9.316,9.499,9.683,9.868,10.054,10.241,10.430,10.620,10.811,11.003,11.197,11.391,11.588,11.785,11.984,12.184,12.386,12.588,12.793,12.998,13.206,13.414,13.624,13.836,14.049,14.264,14.480,14.698,14.917,15.138,15.360,15.585,15.811,16.038,16.268,16.499,16.731};
double RIGHT_UP[193] = {-16.731,-16.499,-16.268,-16.038,-15.811,-15.585,-15.360,-15.138,-14.917,-14.698,-14.480,-14.264,-14.049,-13.836,-13.624,-13.414,-13.206,-12.998,-12.793,-12.588,-12.386,-12.184,-11.984,-11.785,-11.588,-11.391,-11.197,-11.003,-10.811,-10.620,-10.430,-10.241,-10.054,-9.868,-9.683,-9.499,-9.316,-9.135,-8.954,-8.775,-8.597,-8.419,-8.243,-8.068,-7.894,-7.721,-7.549,-7.378,-7.208,-7.039,-6.871,-6.704,-6.538,-6.373,-6.208,-6.045,-5.883,-5.721,-5.560,-5.400,-5.241,-5.083,-4.926,-4.769,-4.613,-4.458,-4.304,-4.151,-3.998,-3.846,-3.695,-3.545,-3.395,-3.246,-3.098,-2.950,-2.803,-2.657,-2.512,-2.367,-2.223,-2.079,-1.937,-1.794,-1.653,-1.512,-1.371,-1.232,-1.093,-0.954,-0.816,-0.679,-0.542,-0.406,-0.270,-0.135,0.000,0.134,0.268,0.401,0.533,0.665,0.797,0.928,1.059,1.189,1.318,1.448,1.576,1.704,1.832,1.960,2.087,2.213,2.339,2.465,2.590,2.715,2.839,2.964,3.087,3.210,3.333,3.456,3.578,3.700,3.821,3.943,4.063,4.184,4.304,4.424,4.543,4.662,4.781,4.899,5.017,5.135,5.253,5.370,5.487,5.604,5.720,5.836,5.952,6.068,6.183,6.298,6.413,6.528,6.642,6.756,6.870,6.984,7.097,7.211,7.324,7.436,7.549,7.661,7.774,7.886,7.997,8.109,8.220,8.332,8.443,8.553,8.664,8.775,8.885,8.995,9.105,9.215,9.325,9.435,9.544,9.653,9.763,9.872,9.981,10.090,10.198,10.307,10.415,10.524,10.632,10.740,10.848,10.956,11.064,11.172,11.280};
double LEFT_DOWN[193] = {11.280,11.172,11.064,10.956,10.848,10.740,10.632,10.524,10.415,10.307,10.198,10.090,9.981,9.872,9.763,9.653,9.544,9.435,9.325,9.215,9.105,8.995,8.885,8.775,8.664,8.553,8.443,8.332,8.220,8.109,7.997,7.886,7.774,7.661,7.549,7.436,7.324,7.211,7.097,6.984,6.870,6.756,6.642,6.528,6.413,6.298,6.183,6.068,5.952,5.836,5.720,5.604,5.487,5.370,5.253,5.135,5.017,4.899,4.781,4.662,4.543,4.424,4.304,4.184,4.063,3.943,3.821,3.700,3.578,3.456,3.333,3.210,3.087,2.964,2.839,2.715,2.590,2.465,2.339,2.213,2.087,1.960,1.832,1.704,1.576,1.448,1.318,1.189,1.059,0.928,0.797,0.665,0.533,0.401,0.268,0.134,0.000,-0.135,-0.270,-0.406,-0.542,-0.679,-0.816,-0.954,-1.093,-1.232,-1.371,-1.512,-1.653,-1.794,-1.937,-2.079,-2.223,-2.367,-2.512,-2.657,-2.803,-2.950,-3.098,-3.246,-3.395,-3.545,-3.695,-3.846,-3.998,-4.151,-4.304,-4.458,-4.613,-4.769,-4.926,-5.083,-5.241,-5.400,-5.560,-5.721,-5.883,-6.045,-6.208,-6.373,-6.538,-6.704,-6.871,-7.039,-7.208,-7.378,-7.549,-7.721,-7.894,-8.068,-8.243,-8.419,-8.597,-8.775,-8.954,-9.135,-9.316,-9.499,-9.683,-9.868,-10.054,-10.241,-10.430,-10.620,-10.811,-11.003,-11.197,-11.391,-11.588,-11.785,-11.984,-12.184,-12.386,-12.588,-12.793,-12.998,-13.206,-13.414,-13.624,-13.836,-14.049,-14.264,-14.480,-14.698,-14.917,-15.138,-15.360,-15.585,-15.811,-16.038,-16.268,-16.499,-16.731};
double RIGHT_DOWN[193] = {16.731,16.499,16.268,16.038,15.811,15.585,15.360,15.138,14.917,14.698,14.480,14.264,14.049,13.836,13.624,13.414,13.206,12.998,12.793,12.588,12.386,12.184,11.984,11.785,11.588,11.391,11.197,11.003,10.811,10.620,10.430,10.241,10.054,9.868,9.683,9.499,9.316,9.135,8.954,8.775,8.597,8.419,8.243,8.068,7.894,7.721,7.549,7.378,7.208,7.039,6.871,6.704,6.538,6.373,6.208,6.045,5.883,5.721,5.560,5.400,5.241,5.083,4.926,4.769,4.613,4.458,4.304,4.151,3.998,3.846,3.695,3.545,3.395,3.246,3.098,2.950,2.803,2.657,2.512,2.367,2.223,2.079,1.937,1.794,1.653,1.512,1.371,1.232,1.093,0.954,0.816,0.679,0.542,0.406,0.270,0.135,0.000,-0.134,-0.268,-0.401,-0.533,-0.665,-0.797,-0.928,-1.059,-1.189,-1.318,-1.448,-1.576,-1.704,-1.832,-1.960,-2.087,-2.213,-2.339,-2.465,-2.590,-2.715,-2.839,-2.964,-3.087,-3.210,-3.333,-3.456,-3.578,-3.700,-3.821,-3.943,-4.063,-4.184,-4.304,-4.424,-4.543,-4.662,-4.781,-4.899,-5.017,-5.135,-5.253,-5.370,-5.487,-5.604,-5.720,-5.836,-5.952,-6.068,-6.183,-6.298,-6.413,-6.528,-6.642,-6.756,-6.870,-6.984,-7.097,-7.211,-7.324,-7.436,-7.549,-7.661,-7.774,-7.886,-7.997,-8.109,-8.220,-8.332,-8.443,-8.553,-8.664,-8.775,-8.885,-8.995,-9.105,-9.215,-9.325,-9.435,-9.544,-9.653,-9.763,-9.872,-9.981,-10.090,-10.198,-10.307,-10.415,-10.524,-10.632,-10.740,-10.848,-10.956,-11.064,-11.172,-11.280};



typedef
struct VEHICLE_INFO
{
	double leftUpAngle;
	double leftDownAngle;
	double rightUpAngle;
	double rightDownAngle;
	double leftUpVelocity;
	double leftDownVelocity;
	double rightUpVelocity;
	double rightDownVelocity;
	double turning_radius;
	double average_velocity;
	int    indexNum;
}
VEHICLE_INFO_t;

VEHICLE_INFO vehicleCtrInfo;

// void angleConvert(double leftAngle, double rightAngle)
// {
// 	if(leftAngle >= 0)
// 	{
// 		if(leftAngle > MAX_LEFT_ANGLE) leftAngle = MAX_LEFT_ANGLE;
// 		vehicleCtrInfo.turning_radius = WHEELBASE/tan(leftAngle*PI/180) + WHEELTRACK/2;
// 		if(vehicleCtrInfo.turning_radius > MAX_RADIUS) vehicleCtrInfo.turning_radius = MAX_RADIUS;
// 		vehicleCtrInfo.leftUpAngle = leftAngle;
// 		vehicleCtrInfo.rightUpAngle = atan(WHEELBASE/(WHEELBASE/tan(vehicleCtrInfo.leftUpAngle*PI/180) + WHEELTRACK))*180/PI;
// 		vehicleCtrInfo.leftDownAngle = 0;
// 		vehicleCtrInfo.rightDownAngle = 0;
// 		vehicleCtrInfo.leftUpVelocity = 0;
// 		vehicleCtrInfo.rightUpVelocity = 0;
// 		vehicleCtrInfo.leftDownVelocity = vehicleCtrInfo.average_velocity*(vehicleCtrInfo.turning_radius - WHEELTRACK/2)/vehicleCtrInfo.turning_radius;
// 		vehicleCtrInfo.rightDownVelocity = vehicleCtrInfo.average_velocity*(vehicleCtrInfo.turning_radius + WHEELTRACK/2)/vehicleCtrInfo.turning_radius;
// 	}
// 	else{
// 		if(rightAngle < MIN_RIGHT_ANGLE) rightAngle = MIN_RIGHT_ANGLE;
// 		vehicleCtrInfo.turning_radius = WHEELBASE/tan(-rightAngle*PI/180) + WHEELTRACK/2;
// 		if(vehicleCtrInfo.turning_radius > MAX_RADIUS) vehicleCtrInfo.turning_radius = MAX_RADIUS;
// 		vehicleCtrInfo.rightUpAngle = rightAngle;
// 		vehicleCtrInfo.leftUpAngle = -atan(WHEELBASE/(WHEELBASE/tan(-vehicleCtrInfo.rightUpAngle*PI/180) + WHEELTRACK))*180/PI;
// 		vehicleCtrInfo.leftDownAngle = 0;
// 		vehicleCtrInfo.rightDownAngle = 0;
// 		vehicleCtrInfo.leftUpVelocity = 0;
// 		vehicleCtrInfo.rightUpVelocity = 0;
// 		vehicleCtrInfo.leftDownVelocity = vehicleCtrInfo.average_velocity*(vehicleCtrInfo.turning_radius + WHEELTRACK/2)/vehicleCtrInfo.turning_radius;
// 		vehicleCtrInfo.rightDownVelocity = vehicleCtrInfo.average_velocity*(vehicleCtrInfo.turning_radius - WHEELTRACK/2)/vehicleCtrInfo.turning_radius;
// 	}
// 	if(vehicleCtrInfo.leftUpAngle > MAX_LEFT_ANGLE) vehicleCtrInfo.leftUpAngle = MAX_LEFT_ANGLE;
// 	if(vehicleCtrInfo.leftUpAngle < MIN_LEFT_ANGLE) vehicleCtrInfo.leftUpAngle = MIN_LEFT_ANGLE;
// 	if(vehicleCtrInfo.rightUpAngle > MAX_RIGHT_ANGLE) vehicleCtrInfo.rightUpAngle = MAX_RIGHT_ANGLE;
// 	if(vehicleCtrInfo.rightUpAngle < MIN_RIGHT_ANGLE) vehicleCtrInfo.rightUpAngle = MIN_RIGHT_ANGLE;
// 	if(vehicleCtrInfo.leftDownVelocity > MAX_VELOCITY) vehicleCtrInfo.leftDownVelocity = MAX_VELOCITY;
// 	if(vehicleCtrInfo.rightDownVelocity > MAX_VELOCITY) vehicleCtrInfo.rightDownVelocity = MAX_VELOCITY;
// 	if(vehicleCtrInfo.leftDownVelocity < 0) vehicleCtrInfo.leftDownVelocity = 0;
// 	if(vehicleCtrInfo.rightDownVelocity < 0) vehicleCtrInfo.rightDownVelocity = 0;
// }

void angleConvert(int indexNum)
{
	vehicleCtrInfo.leftUpAngle = LEFT_UP[indexNum]*1.5; //
	vehicleCtrInfo.rightUpAngle = RIGHT_UP[indexNum]*1.5;
	vehicleCtrInfo.leftDownAngle = LEFT_DOWN[indexNum]*1.5;
	vehicleCtrInfo.rightDownAngle = RIGHT_DOWN[indexNum]*1.5;
	// vehicleCtrInfo.leftUpVelocity = 0;
	// vehicleCtrInfo.rightUpVelocity = 0;
  
	vehicleCtrInfo.turning_radius = abs(WHEELBASE/tan(TURN_IN[indexNum]*PI/180));
	if(vehicleCtrInfo.turning_radius > MAX_RADIUS)	vehicleCtrInfo.turning_radius = MAX_RADIUS;
	if(vehicleCtrInfo.leftUpAngle < 0){
		vehicleCtrInfo.leftDownVelocity = vehicleCtrInfo.average_velocity*(vehicleCtrInfo.turning_radius + WHEELTRACK/2)/vehicleCtrInfo.turning_radius;
		vehicleCtrInfo.rightDownVelocity = vehicleCtrInfo.average_velocity*(vehicleCtrInfo.turning_radius - WHEELTRACK/2)/vehicleCtrInfo.turning_radius;
	}
	else{
		vehicleCtrInfo.leftDownVelocity = vehicleCtrInfo.average_velocity*(vehicleCtrInfo.turning_radius - WHEELTRACK/2)/vehicleCtrInfo.turning_radius;
		vehicleCtrInfo.rightDownVelocity = vehicleCtrInfo.average_velocity*(vehicleCtrInfo.turning_radius + WHEELTRACK/2)/vehicleCtrInfo.turning_radius;
	}
	if(vehicleCtrInfo.leftDownVelocity > MAX_VELOCITY)
	{
		vehicleCtrInfo.leftDownVelocity = MAX_VELOCITY;
		vehicleCtrInfo.rightDownVelocity = vehicleCtrInfo.leftDownVelocity * (vehicleCtrInfo.turning_radius - WHEELTRACK/2)/(vehicleCtrInfo.turning_radius + WHEELTRACK/2);
	} 
	if(vehicleCtrInfo.rightDownVelocity > MAX_VELOCITY)
	{
		vehicleCtrInfo.rightDownVelocity = MAX_VELOCITY;
		vehicleCtrInfo.leftDownVelocity = vehicleCtrInfo.rightDownVelocity * (vehicleCtrInfo.turning_radius - WHEELTRACK/2)/(vehicleCtrInfo.turning_radius + WHEELTRACK/2);
	} 
	if(vehicleCtrInfo.leftDownVelocity < MIN_VELOCITY){
		vehicleCtrInfo.leftDownVelocity = MIN_VELOCITY;
		vehicleCtrInfo.rightDownVelocity = vehicleCtrInfo.leftDownVelocity * (vehicleCtrInfo.turning_radius - WHEELTRACK/2)/(vehicleCtrInfo.turning_radius + WHEELTRACK/2);
	}
	if(vehicleCtrInfo.rightDownVelocity < MIN_VELOCITY){
		vehicleCtrInfo.rightDownVelocity = MIN_VELOCITY;
		vehicleCtrInfo.leftDownVelocity = vehicleCtrInfo.rightDownVelocity * (vehicleCtrInfo.turning_radius - WHEELTRACK/2)/(vehicleCtrInfo.turning_radius + WHEELTRACK/2);
	}

	vehicleCtrInfo.leftUpVelocity = vehicleCtrInfo.leftDownVelocity;
	vehicleCtrInfo.rightUpVelocity = vehicleCtrInfo.rightDownVelocity;
}

void angleConvertStopAndTurn()
{
	vehicleCtrInfo.leftUpAngle = 48.8;
	vehicleCtrInfo.rightUpAngle = -48.8;
	vehicleCtrInfo.leftDownAngle = -48.8;
	vehicleCtrInfo.rightDownAngle = 48.8;

	vehicleCtrInfo.leftDownVelocity = -vehicleCtrInfo.average_velocity;
	vehicleCtrInfo.rightDownVelocity = vehicleCtrInfo.average_velocity;
	vehicleCtrInfo.leftUpVelocity = vehicleCtrInfo.leftDownVelocity;
	vehicleCtrInfo.rightUpVelocity = vehicleCtrInfo.rightDownVelocity;

}


#endif
