#ifndef ITEM_HPP
#define ITEM_HPP

#include "AnimatedSprite.hpp"

class Item: public AnimSprite{
public:
    Item(Anim* a, bool looped=true);
};

#endif // ITEM_HPP
