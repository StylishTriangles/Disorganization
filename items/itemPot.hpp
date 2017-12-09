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
        std::cout << "TWi clicked\n";
    }

    void onDrag(int dx, int dy) override {
        setPosition(dx, dy);
        //std::cout << "moved: " << dx << ", " << dy << "\n";
    };

    void onDrop() override {
        std::cout << "TWi has been planted\n";
    }
};

#endif // ITEM_POT_HPP
