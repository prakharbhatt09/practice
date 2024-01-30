#include<iostream>
#include "findNumber.hpp"

using namespace std;

bool findNumber(const int array[], int size, int target){
    for(int i=0; i<size; i++){
        if(array[i] == target){
            cout<<"At index:"<< i <<endl;
            return true;
        }
    }
    cout<<"Number not found, try again!"<<endl;
    return false;

}

int main(){

    const int myArray[] = {1,2,3,4,5};

    cout<<"Enter a number to search in given array"<<endl;
    int userInput;
    cin>>userInput;

    if(findNumber(myArray, 5, userInput)){
        cout << "Number found"  <<endl;
    }
    return 0;

}