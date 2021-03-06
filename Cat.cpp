#include "cat.hpp"

void Cat::create(std::map<std::string, Anim*> animations) {
	anims = animations;
	setAnimation(animations["catIdle"]);
	Utils::setOriginInCenter(*this);
}

void Cat::update(sf::Time deltaTime) {
	int dT = deltaTime.asMilliseconds();
	if (activePrank != nullptr && activePrank->activeItem != nullptr && (activePrank->activeItem->state & Item::TRASHED)) {
		state = GOINGTOPATH;
		setAnimation(anims["catMove"]);
	}
	if (state == IDLE) {

	}
	else if (state == TRAVEL) {
		if (getPosition().x > activePrank->activeItem->getPosition().x) {
			travelDirection = LEFT;
			setScale(-abs(getScale().x), getScale().y);
		}
		else {
			travelDirection = RIGHT;
			setScale(abs(getScale().x), getScale().y);
		}
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
	else if (state == TRAVELTOCENTER) {
		if (getPosition().x > Settings::roomCenter) {
			travelDirection = LEFT;
			setScale(-abs(getScale().x), getScale().y);
		}
		else {
			travelDirection = RIGHT;
			setScale(abs(getScale().x), getScale().y);
		}
		if (travelDirection == RIGHT) {
			move((float)dT/6.0f, 0);
		}
		else {
			move(-(float)dT/6.0f, 0);
		}
		if (abs(getPosition().x-Settings::roomCenter) < 15) {
			state = IDLE;
			setAnimation(anims["catIdle"]);
			travelDirection = NONE;
		}
	}
	else if (state == PRANK) {
		if (prankProgress > activePrank->prankTime) {
			state = GOINGTOPATH;
			prankProgress = 0;
			setAnimation(anims["catMove"]);
			activePrank->activeItem->changeState();
			activePrank->onFinish();
		}
		else{
            activePrank->onPranking(deltaTime);
		}
		prankProgress += deltaTime.asMilliseconds();
	}
	else if (state == RUN) {
		AnimSprite::update(2*deltaTime.asMilliseconds());
		if (abs(getPosition().x - runTo) < 15) {
			state = TRAVELTOCENTER;
			setAnimation(anims["catMove"]);
		}
        if (travelDirection == RIGHT) {
			move((float)dT * Utils::normalized(sf::Vector2f(runTo, Settings::floorLevel-getPosition().y)));
		}
		else {
			move(-(float)dT * Utils::normalized(sf::Vector2f(runTo, -Settings::floorLevel+getPosition().y)));
		}
	}
	else if (state == CLOSETOPRANK) {
		if (Utils::getMagnitude(getPosition(), activePrank->activeItem->getPosition()) < 100) {
			setScale(-abs(getScale().x) * Utils::sgn(activePrank->activeItem->getPosition().x - getPosition().x), getScale().y);
			//flip();
			setAnimation(activePrank->catAnim);
			activePrank->onStart();
			state = PRANK;
			travelDirection = NONE;
		}
		else {
			move(Utils::normalized(activePrank->activeItem->getPosition() - getPosition()) * (float)dT / 3.0f);
		}
	}
	else if (state == GOINGTOPATH) {
		if (abs(getPosition().y-Settings::floorLevel) < 10) {
			state = TRAVELTOCENTER;
			setAnimation(anims["catMove"]);
		}

		else if (getPosition().y < Settings::floorLevel) {
			move(0, (float)dT / 3.0f);
		}

		else if (getPosition().y > Settings::floorLevel) {
			move(0, -(float)dT / 3.0f);
		}
	}
	else if (state == HISSING) {
		if (getLoops() > 5) {
			do {
				runTo = Utils::randInt(0, Settings::windowSize.x*3);
			}
			while (abs(runTo - getPosition().x) < 500);
			state = RUN;
			if (runTo > getPosition().x)
				travelDirection = RIGHT;
			else
				travelDirection = LEFT;
			prankProgress = 0;
			setAnimation(anims["catMove"]);
			setScale(abs(getScale().x) * Utils::sgn(runTo - getPosition().x), getScale().y);
		}
	}
	AnimSprite::update((state == TRAVELTOCENTER ? 0.5f : 1) * deltaTime.asMilliseconds());
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
	setAnimation(anims["catMove"]);
}

void Cat::getRekt() {
	SoundHandler::playSound(Sounds::cat_screach1);
	state = HISSING;
	setAnimation(anims["catHiss"]);
}

bool Cat::isIdle() {
	return state == IDLE || state == TRAVELTOCENTER;
}
