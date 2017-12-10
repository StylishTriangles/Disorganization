#ifndef ITEM_BED_HPP
#define ITEM_BED_HPP

#include "../item.hpp"

#include <iostream>

class ItemBed : public Item {
public:
    ItemBed(Anim *a, float layer = 0.0)
        : Item(a, BED, layer)
    {
    }

    void onClick() override {
        std::cout << "bed clicked\n";
    }

    void onDrag(int dx, int dy) override {
        if(state == BROKEN){
            repair++;
            if(repair==1)
                SoundHandler::playSound(Sounds::scratch_fast);
            if(repair>100){
                changeState();
                repair=0;
            }
        }
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
            nextFrame();
        }
    }

    int repair=0;
};

#endif // ITEM_BED_HPP
