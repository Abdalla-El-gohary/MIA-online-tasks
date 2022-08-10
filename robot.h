#ifndef ROBOT_H
#define ROBOT_H
#include <iostream>

using namespace std;
class robot
{
    public:

        robot();
        virtual ~robot();
        void addrobot(string n,int *f,int p);
        void displayrobot();
        string getname();
        string getdate(int no_of_dates);
        void adddate(string d,int i);
        void changeboolean();
    protected:

    private:
        string name;
        int functions[5]={0};
        int price;
        bool rented=false;
        string dates[20]={"0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0"};//array of dates rented in the format: day/month/year


};

#endif // ROBOT_H
