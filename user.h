#ifndef USER_H
#define USER_H
#include <iostream>

using namespace std;

class user
{
    public:
        user();
        virtual ~user();
        void adduser(string n,int t,string e);
        void displayuser();
        string getname();
        void addrobotrent(int robotno,int no);

    protected:

    private:
        string name;
        int telephonenumber;
        string email;
        int robotrented[10]={0};
};

#endif // USER_H
