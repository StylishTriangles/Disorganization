#ifndef ITEM_POOL_HPP
#define ITEM_POOL_HPP

#include "../item.hpp"

class ItemPool: public Item{
public:
    ItemPool(Anim* a, float layer=0.0);

    void onClick() override;
};

#endif // ITEM_POOL_HPP
