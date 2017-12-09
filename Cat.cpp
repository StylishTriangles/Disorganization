#include "cat.hpp"

void Cat::create(std::map<std::string, Anim*> animations) {
	anims = animations;
	setAnimation(animations["catIdle"]);
	Utils::setOriginInCenter(*this);
}

void Cat::update(sf::Time deltaTime) {
	int dT = deltaTime.asMilliseconds();
	if (state == IDLE) {

	}
	else if (state == TRAVEL) {
		std::cout << "Travelling";
		if (travelDirection == RIGHT) {
			move((float)dT/3.0f, 0);
		}
		else {
			move(-(float)dT/3.0f, 0);
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
			move(dT, 0);
		}
		else {
			move(-dT, 0);
		}
	}
	else if (state == CLOSETOPRANK) {
		if (abs(getPosition().x-activePrank->activeItem->getPosition().x) < 5) {
			setAnimation(activePrank->catAnim);
			activePrank->onStart();
			state = PRANK;
		}
		else {
			move(Utils::normalized(activePrank->activeItem->getPosition() - getPosition()) * (float)dT / 3.0f);
		}
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
