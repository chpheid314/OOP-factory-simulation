#include "CreamMachine.h"

CreamMachine::CreamMachine()
    : Machine("Cream Machine", 4)
{
}

void CreamMachine::process(Product& product) {

    product.addQuality(10);
}

std::string CreamMachine::getDescription() const
{
    return "Applies cream";
}