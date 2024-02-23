#include <vector>
#include "DFE.hpp"

void DFE::addReceiverInstance(Receiver &receiverObject){
    AssignedReceivers.push_back(receiverObject);
};