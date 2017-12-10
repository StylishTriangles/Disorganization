#ifndef ITEM_TV_HPP
#define ITEM_TV_HPP

#include "../item.hpp"

class ItemTV: public Item{
public:
    ItemTV(Anim* a, float layer=-1.0)
    :Item(a, TV, layer)
    {

    }

    void onClick() override {
        std::cout << "tv clicked\n";
    }
};

#endif // ITEM_TV_HPP
