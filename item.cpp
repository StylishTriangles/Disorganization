#include "Item.hpp"

#include "Utils.hpp"

Item::Item(Anim* a, ItemType i, float _layer)
    :AnimSprite(a),
      layer(_layer)
{
    Utils::setOriginInCenter(*this);
    type = i;
}

void Item::onDrag(int dx, int dy){
    move(dx, dy);
}

void Item::onDrop(){

}

void Item::update(sf::Time dt){

}

void Item::changeState(){

}

void Item::onTrash(Item* trash){

}
