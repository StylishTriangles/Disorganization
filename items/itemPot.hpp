#ifndef ITEM_POT_HPP
#define ITEM_POT_HPP

#include "../item.hpp"

#include <iostream>

class ItemPot: public Item{
public:
    ItemPot(Anim* a, bool looped=true)
    :Item(a, looped)
    {
    }

    void onClick() override {
        std::cout << "pot clicked\n";
    }
};

#endif // ITEM_POT_HPP
