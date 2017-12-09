#include "Item.hpp"

#include "Utils.hpp"

Item::Item(Anim* a, float _layer)
    :AnimSprite(a),
      layer(_layer)
{
    Utils::setOriginInCenter(*this);
}

void Item::onDrag(int dx, int dy){
    move(dx, dy);
}

void Item::onDrop(){

}

void Item::update(sf::Time dt){

}
