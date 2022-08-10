#include "robot.h"
#include <iostream>
#include <string.h>
using namespace std;

robot::robot()     //contructive
{
    //ctor
}

robot::~robot()          //destructive at the end of main
{
    //cout<<"good programmer";
    //dtor
}
void robot::addrobot(string n,int *f,int p){
    robot::name=n;
    for(int qq=0;qq<5;qq++){
        robot::functions[qq]=f[qq];
    }
    robot::price=p;

}
void robot::displayrobot(){
    cout<<"Name of robot:"<<robot::name<<endl;
    cout<<"Robot functions"<<endl;
    for(int qq=0;qq<5;qq++){
            if(robot::functions[qq]==0){
            continue;
        }
        else{
           cout<<robot::functions[qq]<<",";        }

    }
    cout<<endl<<"Price per day:"<<robot::price<<endl;
    cout<<"Dates when robots is rented:"<<endl;
    for(int qq=0;qq<20;qq++){
        if(robot::dates[qq]=="0"){
            continue;
        }
        else{
            cout<<robot::dates[qq]<<endl;
        }
    }
    cout<<endl<<endl;
}
string robot::getname(){
    return robot::name;
}
string robot::getdate(int no_of_dates){
    return robot::dates[no_of_dates];
}
void robot::changeboolean(){
    rented=true;
}
void robot::adddate(string d,int i){
    robot::dates[i]=d;
}

//if you want to access other class use name of class::
