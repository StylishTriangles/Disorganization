#ifndef ITEM_HPP
#define ITEM_HPP

#include "AnimatedSprite.hpp"

class Item: public AnimSprite{
public:
    Item(Anim* a, bool looped=true);

    bool clickable;
    bool dragndrop;

    virtual void onClick()=0;
    virtual void onDrag(int dx, int dy);
    virtual void onDrop();
};

#endif // ITEM_HPP
