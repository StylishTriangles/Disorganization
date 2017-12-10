#ifndef ITEM_GLASS_HPP
#define ITEM_GLASS_HPP

#include "../item.hpp"

#include <iostream>

class ItemGlass : public Item
{
  public:
    ItemGlass(Anim *a, float layer = 0.0)
        : Item(a, GLASS, layer)
    {
        isTrashable = false;
        draggable = false;
    }

    void onClick() override
    {
        std::cout << "glass clicked\n";
    }

    void changeState() override
    {
        if (state == DEFAULT)
        {
            SoundHandler::playSound(Sounds::glass_crash_realistic);
            state = BROKEN;
            isTrashable = true;
            draggable = true;
            nextFrame();
        }
        else if (state == BROKEN)
        {
            state = DEFAULT;
            setColor(sf::Color::White);
        }
    }
};

#endif // ITEM_GLASS_HPP
