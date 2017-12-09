#include "Item.hpp"

#include "Utils.hpp"

Item::Item(Anim* a, float layer)
:AnimSprite(a)
{
    Utils::setOriginInCenter(*this);
}

void Item::Item::onDrag(int dx, int dy){

}

void Item::Item::onDrop(){

}

bool operator < (const Item &lhs, const Item &rhs) {
    return lhs.layer < rhs.layer;
}
