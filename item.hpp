#ifndef ITEM_HPP
#define ITEM_HPP

#include "AnimatedSprite.hpp"

class Item: public AnimSprite{
public:
    Item(Anim* a, float _layer = 1.0f);
    virtual ~Item() = default;

    bool clickable;
    bool dragndrop;
    float layer;

    virtual void onClick() = 0;
    virtual void onDrag(int dx, int dy);
    virtual void onDrop();

    static bool cmpLayer(Item* lhs, Item* rhs) {
        return lhs->layer < rhs->layer;
    }
};

#endif // ITEM_HPP
