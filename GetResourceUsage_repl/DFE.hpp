#ifndef DFE_H
#define DFE_H
#include <iostream>
#include <vector>
#include <cstdint>
#include "Receiver.hpp"

using namespace std;

class DFE{
    private:
    uint8_t NrOfAssignedReceivers;//Max 8

    public:  
    DFE();
    DFE(uint8_t NrOfAssignedReceivers_val)
    :NrOfAssignedReceivers{NrOfAssignedReceivers_val}{
    }

    uint8_t getNrOfAssignedReceivers(){return NrOfAssignedReceivers;}

    void setNrOfAssignedReceivers(uint8_t t){NrOfAssignedReceivers = t;}

    void addDFEInstance(DFE);

    vector<Receiver> AssignedReceivers;
};
#endif