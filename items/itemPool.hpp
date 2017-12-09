#ifndef ITEM_POOL_HPP
#define ITEM_POOL_HPP

#include "../item.hpp"

class ItemPool: public Item{
public:
    ItemPool(Anim* a, float layer=0.0);

    void onClick() override;
    void onDrag(int dx, int dy) override;
    void onDrop() override;

    float actLevel=0;
    float cleanLevel=500.0;
};

#endif // ITEM_POOL_HPP
