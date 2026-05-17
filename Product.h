#pragma once

#include "CakeType.h"

class Product {
public:
    Product();
    Product(int id, CakeType type);

    int getId() const;
    CakeType getCakeType() const;

    int getQuality() const;
    void addQuality(int value);

    bool isBurned() const;
    void burn();

    bool isCompleted() const;
    void complete();

private:
    int productId;
    CakeType cakeType;

    int quality;

    bool burned;
    bool completed;
};