#include <iostream>
int output[200];
int count1=0;
using namespace std;
void test(int n, int*h){
    int seen, t,test=1;
    while(test<n){
            seen=1;
            t=*(h+test);
            if(*(h+test-1)<*(h+test)){
                seen=1;
            }
            else{
                for(int i=test;i<n-1;i++){
                    if(*(h+i+1)>t){
                    seen++;
                     t=*(h+i+1);
                }
            }
    }
    output[count1]=seen;
   // cout<<seen;
    count1++;
    test++;
    }
    output[count1]=0;
    count1++;

}
int main()
{
    int q,n;
    int heights[100];
    cin >>q;
    while(q>30 || q<0){
        cout << "invalid input,Enter a number from(1:30)";
        cin >>q;
    }
    while(q--){
        cin >> n;
        for(int i=0;i<n;i++){
            cin >> heights[i];
            for(int j=0;j<i;j++){
                if (heights[j]==heights[i]){
                    cout<< "duplicated number"<<endl;
                    cin>>heights[i];
                    break;
                }
            }
        }
        test(n,heights);
    }
    for(int a =0;a<count1;a++){
        if(output[a]==0){
            cout<<0<<endl;
        }
        else{
            cout<<output[a];
        }
    }
    return 0;
}
