#include "user.h"
#include <iostream>

using namespace std;
user::user()
{
    //ctor
}

user::~user()
{
    //dtor
}
void user::adduser(string n,int t,string e){
    user::name=n;
    user::telephonenumber=t;
    user::email=e;
}
void user::displayuser(){
    cout<<"User name:"<<user::name<<endl;
    cout<<"User telephone number:"<<user::telephonenumber<<endl;
    cout<<"User email:"<<user::email<<endl;
    cout<<"Robots rented:"<<endl;
    for(int qq=0;qq<10;qq++){
        if(user::robotrented[qq]==0){
            continue;
        }
        else{
            cout<<user::robotrented[qq]<<",";
        }
    }
    cout<<endl<<endl;
}
string user::getname(){
    return name;
}
void user::addrobotrent(int robotno,int no){
    robotrented[no]=robotno;
}
