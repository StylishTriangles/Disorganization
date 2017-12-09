#ifndef ITEM_GAMEPAD_HPP
#define ITEM_GAMEPAD_HPP

#include "../item.hpp"

class ItemGamepad: public Item{
public:
    ItemGamepad(Anim *a, float layer)
    :Item(a, GAMEPAD, layer)
    {
        setScale(0.25, 0.25);
    }

    void onClick() override {

    }
};

#endif // ITEM_GAMEPAD_HPP
