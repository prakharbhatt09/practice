#include<iostream>

using namespace std;

bool isPrime(int num){
    if (num<=1){
        cout<<"Number isn't Prime"<<endl;
        return false;
    }
    if (num<=3){
        cout<<"Number is Prime"<<endl;
        return true;
    }
    for (int i=2; i<num; i++){
        if (num%i==0){
            cout<<"Number isn't Prime"<<endl;
            return false;
        }
    }
    cout<<"Number is Prime"<<endl;
    return true;
}

int main(){

    cout<<"Enter a number to check Prime"<<endl;
    int userInput;
    cin>>userInput;

    bool output = isPrime(userInput);
}