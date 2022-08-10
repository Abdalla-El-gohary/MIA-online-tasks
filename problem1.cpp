#include <iostream>

using namespace std;
//function to print hi by astress
void printhi(){
    for(int i =0;i<5;i++){
        if(i==2){
            cout << "******    *"<<endl;
        }
        else{
            cout << "*    *  ";
            if(i == 0)
                cout <<"*****"<<endl;
            else if(i == 4)
                cout <<"*****"<<endl;
            else
                cout << "  *"<<endl;
        }

    }
}
int main()
{
    printhi();
    return 0;
}
