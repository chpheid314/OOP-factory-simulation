#include "ToppingMachine.h"

ToppingMachine::ToppingMachine()
    : Machine("Topping Machine", 5)
{
}

void ToppingMachine::process(Product& product) {

    switch(product.getCakeType())
    {
    case CakeType::CHOCOLATE:

        product.addQuality(15);

        if(rand()%10==0)
            product.burn();

        break;

    case CakeType::STRAWBERRY:

        product.addQuality(20);

        break;

    case CakeType::MATCHA:

        product.addQuality(10);

        break;
    }

    product.complete();
}

std::string ToppingMachine::getDescription() const
{
    return "Adds toppings";
}