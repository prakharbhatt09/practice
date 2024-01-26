#include<iostream>


using namespace std;

float sum(float x, float y){
    return (x+y);
}

int main(){
    float num1;
    float num2;
    float output;
    cout<<"Enter first number"<<endl;
    cin>>num1;
    cout<<"Enter second number"<<endl;
    cin>>num2;

    output = sum(num1, num2);
    cout<<"Sum of "<<num1<<" and "<<num2<<" is "<<output<<endl;
}