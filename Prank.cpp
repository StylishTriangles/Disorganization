#include "prank.hpp"

Prank::Prank(std::map<std::string, Item*>* its, int xPosition)
:items(its)
{
	xCoord = xPosition;
}

void Prank::onFinish() {

}
