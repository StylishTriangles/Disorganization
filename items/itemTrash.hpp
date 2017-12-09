#ifndef ITEMTRASH_H
#define ITEMTRASH_H

#include "../item.hpp"

class ItemTrash : public Item
{
public:
    ItemTrash(Anim *a, float _layer = 1.0f);

    void onClick() override {} // NO CLICKING

    void changeState() override;
};

#endif // ITEMTRASH_H
