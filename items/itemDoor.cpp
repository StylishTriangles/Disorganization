#include "itemDoor.hpp"

#include "../game.hpp"

ItemDoor::ItemDoor(Anim *a, bool lDoors, float layer = 0.0)
:Item(a, Item::DOOR, layer), leftDoors(lDoors)
{
}

void ItemDoor::onClick()
{
    if(leftDoors)
        g->view.move(-1280, 0);
    else
        g->view.move(1280, 0);
}

void ItemDoor::onDrag(int dx, int dy)
{
    //move(dx, dy);
}

void ItemDoor::onDrop()
{
    //std::cout << "pot has been planted\n";
}

void ItemDoor::changeState() {

}

void ItemDoor::setGame(Game *gam) {
    g = gam;
}
