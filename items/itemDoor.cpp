#include "itemDoor.hpp"

#include "../game.hpp"

ItemDoor::ItemDoor(Anim *a, bool lDoors, float layer = 0.0)
:Item(a, Item::DOOR, layer), leftDoors(lDoors)
{
}

void ItemDoor::onClick(){
    if(leftDoors){
        SoundHandler::playSound(Sounds::door_close);
        Settings::room--;
        g->view.move(-Settings::windowSize.x, 0);
    }
    else{
        SoundHandler::playSound(Sounds::door_open);
        Settings::room++;
        g->view.move(Settings::windowSize.x, 0);
    }
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
