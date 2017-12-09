#include "cat.hpp"

void Cat::create(std::map<std::string, Anim*> anims) {
	setAnimation(anims["catIdle"]);
}

void Cat::update(sf::Time deltaTime, std::map<std::string, Anim*> anims) {
	if (state == IDLE) {

	}
	else if (state == TRAVEL) {
		if (travelDirection = RIGHT) {
			move(5, 0);
		}
		else {
			move(-5, 0);
		}
	}
	else if (state == PRANK) {
		if (prankProgress > activePrank->prankTime) {
			state = IDLE;
			prankProgress = 0;
			setAnimation(anims["catIdle"]);
			activePrank->onFinish();
		}
		prankProgress += deltaTime.asMilliseconds();
	}
	else if (state == RUN) {
		if (travelDirection = RIGHT) {
			move(15, 0);
		}
		else {
			move(-15, 0);
		}
	}
	AnimSprite::update(deltaTime.asMilliseconds());
}

void Cat::setNextPrank(Prank* prank) {
	activePrank = prank;
	if (prank->xCoord > getPosition().x) {
		travelDirection = RIGHT;
	}
	else {
		travelDirection = LEFT;
	}
	state = TRAVEL;
}

bool Cat::isIdle() {
	return state == IDLE;
}
