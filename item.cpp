#include "Item.hpp"

#include "Utils.hpp"

Item::Item(Anim* a, bool looped)
:AnimSprite(a, looped)
{
    Utils::setOriginInCenter(*this);
}

void Item::Item::onDrag(int dx, int dy){

}

void Item::Item::onDrop(){

}
