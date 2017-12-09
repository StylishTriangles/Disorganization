#ifndef CAT_HPP
#define CAT_HPP

#include "AnimatedSprite.hpp"
#include "prank.hpp"
#include <string>

enum catState {
	IDLE,
	TRAVEL,
	PRANK,
	RUN
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


	void create(std::map<std::string, Anim*>);
	void update(sf::Time, std::map<std::string, Anim*>);
	void setNextPrank(Prank*);
	bool isIdle();
	//void
};

#endif // CAT_HPP
