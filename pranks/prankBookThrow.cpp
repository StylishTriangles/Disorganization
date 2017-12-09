#include "prankBookThrow.hpp"

PrankBookThrow::PrankBookThrow(std::map<std::string, Item*>* its)
:Prank(its)
{

}

bool PrankBookThrow::isAvailable(){
	return true;
}
