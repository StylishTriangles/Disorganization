#ifndef CAT_HPP
#define CAT_HPP

#include "AnimatedSprite.hpp"
#include "prank.hpp"
#include "Utils.hpp"
#include <string>
#include <cmath>

enum catState {
	IDLE,
	TRAVEL,
	PRANK,
	RUN,
	CLOSETOPRANK,
	GOINGTOPATH
};

enum direction {
	NONE,
	LEFT,
	RIGHT
};

class Cat : public AnimSprite {
public:
	catState state = IDLE;
	direction travelDirection = NONE;
	Prank* activePrank = nullptr;
	int prankProgress;
	std::map<std::string, Anim*> anims;
	int pathCoordY = 400;


	void create(std::map<std::string, Anim*>);
	void update(sf::Time);
	void setNextPrank(Prank*);
	bool isIdle();
	//void
};

#endif // CAT_HPP
