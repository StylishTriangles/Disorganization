#ifndef ITEMTRASH_H
#define ITEMTRASH_H

#include "../item.hpp"

class ItemTrash : public Item
{
public:
    ItemTrash(Anim *a, float _layer = 1.0f);

    void onClick() override {} // NO CLICKING

    void onDrag(int, int) override {} // PLS DON'T DRAG

    void onDrop() override {} // YOU SERIOUS?

    void changeState() override;
};

#endif // ITEMTRASH_H
