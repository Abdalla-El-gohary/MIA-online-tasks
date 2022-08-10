#include <iostream>

using namespace std;

int testcase[30];
void test(int hp1,int p,int h,int z){
    float hp = float(hp1);
    for(int i=0;i<p;i++){
         hp= hp/2.0 +10.0;
    }
    hp = hp - h*10.0;
    //cout << hp <<endl;
    if(hp<=0){
        *(testcase+z)=1;
    }
    else{
        *(testcase+z)=0;
    }

}
int main()
{
    int q,hp,p,h;
    cin >> q;
    while(q>30 || q<0){
        cout << "invalid input,Enter a number from(1:30)";
        cin >>q;
    }
    int i=0;
    int a=q;
    while(q--){
        cin >> hp;
        while(hp>100000 || hp<0){
        cout << "invalid input,Enter a number from(1:10^5)";
        cin >>hp;
        }
        cin >> p;
        while(p>30 || p<0){
        cout << "invalid input,Enter a number from(1:30)";
        cin >>p;
        }
        cin >>h;
        while(h>30 || h<0){
        cout << "invalid input,Enter a number from(1:30)";
        cin >>h;
        }
        test(hp,p,h,i);
        i++;
    }
    for(int j=0;j<a;j++){
        if(testcase[j]==1)
           cout<< "Yes"<<endl;
        else
            cout<< "No"<<endl;
    }
    return 0;
}
