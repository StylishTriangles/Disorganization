#include "itemPool.hpp"

ItemPool::ItemPool(Anim* a, float layer)
:Item(a, POOL, layer)
{
    state = BROKEN;
}

void ItemPool::onClick(){

}

void ItemPool::onDrag(int dx, int dy){
    actLevel += sqrt(abs(dx)+abs(dy));
    if(actLevel >= cleanLevel)
        actLevel = cleanLevel;
    sf::Color col = getColor();
    col.a = ((cleanLevel-actLevel)/cleanLevel)*255.0f;
    setColor(col);
    if(actLevel >= cleanLevel){
        state = DELETED;
    }
}
