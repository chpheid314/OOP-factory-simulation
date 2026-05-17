#include "ToppingMachine.h"

ToppingMachine::ToppingMachine()
    : Machine("Topping Machine", 5, 0.05f)
{
}

void ToppingMachine::process(Product& product) {

    product.addQuality(15);

    if (product.getCakeType() == CakeType::CHOCOLATE) {

        if (rand() % 10 == 0) {

            product.burn();
        }
    }

    product.complete();
}

std::string ToppingMachine::getName() const {

    return "Adds toppings";
}