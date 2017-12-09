#include "prankBookThrow.hpp"

#include "../game.hpp"

PrankBookThrow::PrankBookThrow(Game* g)
:Prank(g)
{
	activeItem = (g->items)["pot"];
	catAnim = g->anims["catPrankBookThrow"];
}

bool PrankBookThrow::isAvailable(){
	return true;
}

void PrankBookThrow::onStart() {

}

void PrankBookThrow::onFinish() {

}
