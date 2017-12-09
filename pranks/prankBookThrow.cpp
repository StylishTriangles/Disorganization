#include "prankBookThrow.hpp"

PrankBookThrow::PrankBookThrow(std::map<std::string, Item*>* its)
:Prank(its)
{
	activeItem = (*its)["pot"];
}

bool PrankBookThrow::isAvailable(){
	return true;
}
