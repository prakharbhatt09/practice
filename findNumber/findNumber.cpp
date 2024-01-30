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