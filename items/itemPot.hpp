#ifndef ITEM_POT_HPP
#define ITEM_POT_HPP

#include "../item.hpp"

#include <iostream>

class ItemPot: public Item{
public:
    ItemPot(Anim* a, float layer=0.0)
    :Item(a, layer)
    {
    }

    void onClick() override {
        std::cout << "pot clicked\n";
    }

    void onDrag(int dx, int dy) override {
        move(dx, dy);
    }

    void onDrop() override {
        std::cout << "pot has been planted\n";
    }
};

#endif // ITEM_POT_HPP
