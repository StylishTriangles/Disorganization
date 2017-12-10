#include "itemPool.hpp"
#include <cmath>

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
    col.a = ((cleanLevel-actLevel+220)/(cleanLevel+220))*255.0f; // +220, zeby bylo widac
    setColor(col);
    if(actLevel >= cleanLevel){
        state = DELETED;
    }
}
