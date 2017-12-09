#include "cat.hpp"

void Cat::update(sf::Time deltaTime, std::map<std::string, Anim*> anims) {
	if (state == IDLE) {

	}
	else if (state == TRAVEL) {

	}
	else if (state == PRANK) {
		if (prankProgress > activePrank->prankTime) {
			state = IDLE;
			prankProgress = 0;
			setAnimation(anims["catIdle"]);
		}
	}
	else if (state == RUN) {

	}
	AnimSprite::update(deltaTime.asMilliseconds());
}

void Cat::setNextPrank(Prank* prank) {
	activePrank = prank;
}

bool Cat::isIdle() {
	return state == IDLE;
}
