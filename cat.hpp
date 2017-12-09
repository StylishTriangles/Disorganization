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

class Cat : public AnimSprite {
public:
	catState state = IDLE;
	Prank* activePrank = nullptr;
	float prankProgress;



	void update(sf::Time, std::map<std::string, Anim*>);
	void setNextPrank(Prank*);
	bool isIdle();
	//void
};

#endif // CAT_HPP
