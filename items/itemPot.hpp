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

    void onDrag(int dx, int dy) override {
        move(dx, dy);
    };

    void onDrop() override {
        std::cout << "pot has been planted\n";
    }
};

#endif // ITEM_POT_HPP
