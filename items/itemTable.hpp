#ifndef ITEM_TABLE_HPP
#define ITEM_TABLE_HPP

#include "../item.hpp"

#include <iostream>

class ItemTable : public Item
{
  public:
    ItemTable(Anim *a, float layer = 0.0)
        : Item(a, TABLE, layer)
    {
    }

    void onClick() override
    {
        std::cout << "table clicked\n";
    }

    void onDrag(int dx, int dy) override
    {
        //std::cout << getPosition().x << " " << getPosition().y << "\n";
        //move(dx, dy);
    }

    void onDrop() override
    {
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

#endif // ITEM_TABLE_HPP
