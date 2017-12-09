#include "itemTrash.hpp"
#include "../random.hpp"

ItemTrash::ItemTrash(Anim *a, float _layer)
:Item(a, Item::TRASH, _layer)
{
    clickable=true;
    // WOW CONGRATS YOU CONSTRUCTED TRASH
}

void ItemTrash::onClick() {
    if (myItems.empty()) {
        return;
    }
   Item* top = myItems.top();

   sf::Vector2f mypos = this->getPosition();
   mypos.x += randInt(-75,75);
   top->setPosition(mypos);
   top->state = DEFAULT;

   myItems.pop();
}

void ItemTrash::insert(Item* item) {
    myItems.push(item);
}
