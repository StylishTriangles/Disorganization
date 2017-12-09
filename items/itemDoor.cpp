#include "itemDoor.hpp"

#include "../game.hpp"

ItemDoor::ItemDoor(Anim *a, float layer = 0.0)
    : Item(a, layer)
{
}

void ItemDoor::onClick()
{
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

void ItemDoor::setGame(Game *gam) {
    g = gam;
}