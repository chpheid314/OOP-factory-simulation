#include "SheetMachine.h"

SheetMachine::SheetMachine()
    : Machine("Sheet Machine", 3)
{
}

void SheetMachine::process(Product& product) {

    product.addQuality(5);
}

std::string SheetMachine::getDescription() const
{
    return "Creates cake sheets";
}