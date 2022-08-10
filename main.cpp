#include <iostream>
#include "robot.h"
#include "user.h"
using namespace std;
void menulist(){
    cout<<"choose No. of function you want of of the following"<<endl;
    cout<<"1-Add robot"<<endl<<"2-Add user"<<endl<<"3-Display all users"<<endl<<"4-Display all robots"<<endl<<"5-Search for robot by name"<<endl;
    cout<<"6-Search for user by name"<<endl<<"7-Rent robot for user"<<endl<<"8-Exit"<<endl;
}
void fun_id_print(){
        cout<<"1-cleaner robot"<<endl;
        cout<<"2-driver robot"<<endl;
        cout<<"3-assignment robot"<<endl;
        cout<<"4-cook robot"<<endl;
        cout<<"5-hairstylist robot"<<endl;
}
int main()
{
    int countrobot=3;
    int countuser=3;
    robot r[20];
    user u[20];
    int f[5]={1,2,5,0,0};
    r[0].addrobot("Messi",f,250);
    f[2]=4;
    r[1].addrobot("Ronaldo",f,150);
    f[2]=3;
    r[2].addrobot("Salah",f,200);
    f[0]=0;f[1]=0;f[2]=0;

    u[0].adduser("Ahmed",1121415216,"Ahmed@gmail.com");
    u[1].adduser("Hady",1212451261,"Hady@gmail.com");
    u[2].adduser("Ali",1021415631,"Ali@gmail.com");//0 convert to octal

    int choosen;
    string n;//name of robot or user
    int p;//price per day
    string d;//date to rent on
    int no_dates_time[20]={0};//shows number of dates for each robot
    int no_robot_rented[20]={0};//shows number of robots rented for each user
    int robotavailable[20]={0};//to make sure that the user won't choose unavailable robot
    int t;//telephone number
    string e;//email
    int found=100;//to search for user or robot;
    int no_of_functions;//to detect no.of function that robot can do



    menulist();
    cout<<"choose No. of function you want of of the following"<<endl;
    cin>>choosen;
    while(choosen<=0||choosen>8){
        cout<<"invalid input,please enter a number from 1-8"<<endl;
        cin>>choosen;
    }
    while(choosen!=8){
        switch(choosen){
        case 1:
            cout<<"Enter The robot name"<<endl;
            cin>>n;
            cout<<"Enter number of functions he can do(at most 5)"<<endl;
            cin>>no_of_functions;
            fun_id_print();
            cout<<"Enter the function_id's"<<endl;
            for(int i=0;i<no_of_functions;i++){
                cin>>f[i];
            }
            cout<<"Enter price per day"<<endl;
            cin>>p;
            r[countrobot].addrobot(n,f,p);
            countrobot++;
            for(int i=0;i<5;i++){
                f[i]=0;
            }
            break;
        case 2:
            cout<<"Enter The user name"<<endl;
            cin>>n;
            cout<<"Enter telephone number"<<endl;
            cin>>t;
            cout<<"Enter the email"<<endl;
            cin>>e;
            u[countuser].adduser(n,t,e);
            countuser++;
            break;
        case 3:
            for(int i=0;i<countuser;i++){
                    u[i].displayuser();
            }
            break;
        case 4:
            for(int i=0;i<countrobot;i++){
                 r[i].displayrobot();
            }
            break;
        case 5:
            cout<<"Enter the name of robot"<<endl;
            cin>>n;
            for(int i=0;i<countrobot;i++){
                if(r[i].getname() ==n){
                    found=i;
                    break;
                }
            }
            if(found==100){
                cout<<"Not found"<<endl;
            }
            else{
                 r[found].displayrobot();
            }
            found=100;
            break;
        case 6:
            cout<<"Enter the name of user"<<endl;
            cin>>n;
            for(int i=0;i<countuser;i++){
                if(u[i].getname() ==n){
                    found=i;
                    break;
                }
            }
            if(found==100){
                cout<<"Not found"<<endl;
            }
            else{
                 u[found].displayuser();
            }
            found=100;
            break;
        case 7:{
            cout<<"Choose which user you want to rent to from the following list(choose number of him)"<<endl;
            for(int i=0;i<countuser;i++){
                    cout<<i+1<<"-";
                    u[i].displayuser();
            }
            int q;
            cin>>q;
            while(q<0||q>countuser){
                cout<<"invalid user,Enter again"<<endl;
                cin>>q;
            }
            cout<<"Enter the data you want to rent robot on in the format day/month/year"<<endl;
            cin>>d;
            int checkrent=0;
            for(int i=0;i<countrobot;i++){
                for(int j=0;j<20;j++){
                    if(r[i].getdate(j)==d){
                        checkrent=1;
                        break;
                    }

                }
                if(checkrent!=1){
                    robotavailable[i]=i+1;
                    cout<<r[i].getname()<<" robot is available on that day"<<endl;
                }
            }
            cout<<"choose which robot to rent"<<endl;
            int z,check=1;
            cin>>z;
            while(check){
                for(int x=0;x<20;x++){
                      if(z==robotavailable[x]){
                      check=0;}
                      }
                if(check==0){
                     break;
                }
                else{
                    cout<<"unavailable robot,choose another one";
                    cin>>z;
                }
            }
            for(int zx=0;zx<20;zx++){
                robotavailable[zx]=0;
            }
            cout<<"rent successfully"<<endl;
            int x=z-1;
            r[x].changeboolean();
            r[x].adddate(d,no_dates_time[x]);
            no_dates_time[x]++;
            int v=q-1;
            u[v].addrobotrent(z,no_robot_rented[v]);
            no_robot_rented[v]++;
            break;}

        default :
            cout<<"incorrect chose,please enter again"<<endl;
            break;
        }
        cout<<"choose No. of function you want of of the following"<<endl;
        cin>>choosen;
        while(choosen<0||choosen>8){
        cout<<"invalid input,please enter a number from 1-8"<<endl;
        cin>>choosen;
    }
    }
    return 0;
}
