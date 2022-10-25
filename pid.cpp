#include "pid.h"

pid::pid(float set){ 
    pid::setpoint =set;
} //when you create an object from that class you should pass set point as aparameter
pid::~pid(){

}
void pid::setPIDParameters(float kp,float ki,float kd){
    //function to set kp and ki and kd constants
    pid::kp =kp;
    pid::ki =ki;
    pid::kd= kd;
}
void pid::setPoint(float set){
  pid::setpoint =set;
  }

void pid::setStartTime(unsigned long t){
    pid::lastTime =t/1000;
}

long long int pid::compute(unsigned long currentTime, float input){
    //function to calculate the output
    float error = pid::setpoint - input;
    unsigned long deltaT = currentTime/1000 - pid::lastTime;
    pid::sumError+= error *deltaT;
    double errorSlope = (error - pid::lastError)/deltaT;
    float pid_p = pid::kp * error;
    float pid_i = pid::ki * pid::sumError;
    float pid_d = pid::kd * errorSlope;
    pid::lastError=error;
    pid::lastTime=currentTime/1000;
    return pid_p+pid_i+pid_d ;

}


float pid::getP(){
    return pid::kp;
}

float pid::getI(){
    return pid::ki;
}

float pid::getD(){
    return pid::kd;
}

float pid::getSetPoint(){
    return pid::setpoint;
}
