#include "itemGamepad.hpp"

#include "../game.hpp"

ItemGamepad::ItemGamepad(Anim *a, Game* g, float layer)
:Item(a, GAMEPAD, layer), game(g)
{
    setScale(0.25, 0.25);
}

void ItemGamepad::onClick() {

}

void ItemGamepad::update(sf::Time dt) {
    if(state < TRASHED){
        if(Collision::PixelPerfectTest(*game->items["tv"], *this) || Collision::PixelPerfectTest(*game->items["tvScreen"], *this)){
            state = DEFAULT;
        }
        else{
            state = BROKEN;
        }
    }
}

