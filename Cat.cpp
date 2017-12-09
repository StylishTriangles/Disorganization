#include "cat.hpp"

void Cat::create(std::map<std::string, Anim*> animations) {
	anims = animations;
	setAnimation(animations["catIdle"]);
	Utils::setOriginInCenter(*this);
}

void Cat::update(sf::Time deltaTime) {
	if (state == IDLE) {

	}
	else if (state == TRAVEL) {
        if (travelDirection == RIGHT) {
			move(5, 0);
		}
		else {
			move(-5, 0);
		}
		if (abs(getPosition().x-activePrank->activeItem->getPosition().x) < 15) {
			state = CLOSETOPRANK;
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
        if (travelDirection == RIGHT) {
			move(15, 0);
		}
		else {
			move(-15, 0);
		}
	}
	else if (state == CLOSETOPRANK) {

			setAnimation(activePrank->catAnim);
			activePrank->onStart();
	}
	AnimSprite::update(deltaTime.asMilliseconds());
}

void Cat::setNextPrank(Prank* prank) {
	activePrank = prank;
	if (prank->activeItem->getPosition().x > getPosition().x) {
		travelDirection = RIGHT;
		setScale(abs(getScale().x), getScale().y);
	}
	else {
		travelDirection = LEFT;
		setScale(-abs(getScale().x), getScale().y);
	}
	state = TRAVEL;
}

bool Cat::isIdle() {
	return state == IDLE;
}
