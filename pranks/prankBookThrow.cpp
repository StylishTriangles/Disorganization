#include "prankBookThrow.hpp"

PrankBookThrow::PrankBookThrow(std::map<std::string, Item*>* its, int xPosition)
:Prank(its, xPosition)
{

}

bool PrankBookThrow::isAvailable(){
	return true;
}
