#ifndef PID_H
#define PID_H

class pid
{
    public:
        pid(float set);  //constructor
        virtual ~pid();
        void setPIDParameters(float kp,float ki,float kd);
        void setPoint(float set);
        float getP();
        float getI();
        float getD();
        float getSetPoint();
        void setStartTime(unsigned long t);
        long long int compute(unsigned long currentTime, float input);

    protected:

    private:
        float kp=12.0;
        float ki=20.0;
        float kd=0.8;
        float setpoint=0;
        double sumError=0;
        double lastError=0;
        unsigned long lastTime=0;

};

#endif // PID_H
