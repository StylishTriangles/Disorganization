#include "prankBookThrow.hpp"

#include "../game.hpp"

PrankBookThrow::PrankBookThrow(Game* g)
:Prank(g)
{
	activeItem = (g->items)["pot"];
}

bool PrankBookThrow::isAvailable(){
	return true;
}
