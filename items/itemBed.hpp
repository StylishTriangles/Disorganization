#ifndef ITEM_BED_HPP
#define ITEM_BED_HPP

#include "../item.hpp"

#include <iostream>

class ItemBed : public Item
{
  public:
    ItemBed(Anim *a, float layer = 0.0)
        : Item(a, BOOK, layer)
    {
    }

    void onClick() override {
        std::cout << "bed clicked\n";
    }

    void onDrag(int dx, int dy) override {

    }

    void onDrop() override {
        
    }

    void changeState() override
    {
        if (state == DEFAULT)
        {
            state = BROKEN;
            nextFrame();
        }
        else if (state == BROKEN)
        {
            state = DEFAULT;
            setColor(sf::Color::White);
        }
    }
};

#endif // ITEM_BED_HPP
