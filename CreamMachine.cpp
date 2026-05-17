#include "CreamMachine.h"

CreamMachine::CreamMachine()
    : Machine("Cream Machine", 4, 0.02f)
{
}

void CreamMachine::process(Product& product) {

    product.addQuality(10);
}

std::string CreamMachine::getName() const {

    return "Applies cream";
}