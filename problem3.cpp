#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
using namespace std;
char output[1000];
int count1=0;

void encrypt(string input){
    int n = input.length();
    char arr[n+1];
    strcpy(arr,input.c_str());
    int r;
    for(int i=0;i<n;i++){
           if(arr[i+2]=='&'){
                if(arr[i]=='1'){
                    r=int(arr[i+1])-48;
                    output[count1]= 'j'+r;
                    count1++;
                }
                else if(arr[i]=='2'){
                    r=int(arr[i+1])-38;
                    output[count1]= 'j'+r;
                    count1++;
                }
                i+=2;
        }
        else{
            r=int(arr[i])-49;
            output[count1]= 'a'+r;
            count1++;
        }
    }
    output[count1]='\n';
    count1++;
}
int main()
{
    int q;
    string input;
    cin >>q;
    while(q>30 || q<0){
        cout << "invalid input,Enter a number from(1:30)";
        cin >>q;
    }
    while(q--){
        cin>> input;
        encrypt(input);
    }
    for(int i=0;i<count1;i++){
        if(output[i]=='\n'){
            cout<<endl;
        }
        else{
            cout<<output[i];
        }
    }
    return 0;
}
