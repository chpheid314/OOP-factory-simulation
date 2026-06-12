#include "Product.h"

Product::Product()
    : productId(0),
      cakeType(CakeType::CHOCOLATE),
      quality(50),
      burned(false),
      completed(false)
{
}

Product::Product(int id, CakeType type)
    : productId(id),
      cakeType(type),
      quality(50),
      burned(false),
      completed(false)
{
}

int Product::getId() const {
    return productId;
}

CakeType Product::getCakeType() const {
    return cakeType;
}

int Product::getQuality() const {
    return quality;
}

void Product::addQuality(int value) {
    quality += value;

    if (quality > 100)
        quality = 100;

    if (quality < 0)
        quality = 0;
}

bool Product::isBurned() const {
    return burned;
}

void Product::burn() {
    burned = true;
    quality -= 30;

    if (quality < 0)
        quality = 0;
}

bool Product::isCompleted() const {
    return completed;
}

void Product::complete() {
    completed = true;
}