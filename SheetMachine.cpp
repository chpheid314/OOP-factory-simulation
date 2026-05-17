#include "SheetMachine.h"

SheetMachine::SheetMachine()
    : Machine("Sheet Machine", 3, 0.03f)
{
}

void SheetMachine::process(Product& product) {

    product.addQuality(5);
}

std::string SheetMachine::getName() const {

    return "Creates cake sheets";
}