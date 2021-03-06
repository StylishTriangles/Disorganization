#include "itemTrash.hpp"
#include "../random.hpp"

ItemTrash::ItemTrash(Anim *a, float _layer)
:Item(a, Item::TRASH, _layer)
{
    clickable=true;
    // WOW CONGRATS YOU CONSTRUCTED TRASH
}

void ItemTrash::onClick() {
}

void ItemTrash::onRightClick() {
    if (myItems.empty()) {
        return;
    }
    Item* top = myItems.top();

    sf::Vector2f mypos = this->getPosition();
    mypos.x += randInt(-120,120);
    top->setPosition(mypos);
    top->state = (Item::ItemState)(top->state ^ Item::TRASHED);

    myItems.pop();
}

void ItemTrash::insert(Item* item) {
    myItems.push(item);
}
