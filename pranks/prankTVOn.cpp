#include "prankTVOn.hpp"

#include "../game.hpp"

PrankTVOn::PrankTVOn(Game* g)
:Prank(g)
{
    catAnim = g->anims["catPrankBookThrow"];
}

bool PrankTVOn::isAvailable(){
    prankTime = 1000;
    if(game->items["tv"]->state == Item::DEFAULT){
        activeItem = game->items["TVonoff_button"];
        return true;
    }
    else{
        activeItem = nullptr;
        return false;
    }
}

void PrankTVOn::PrankTVOn::onFinish() {
    game->items["tv"]->changeState();
	available = false;
    activeItem=nullptr;
}
