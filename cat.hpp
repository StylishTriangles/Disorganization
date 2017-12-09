#ifndef CAT_HPP
#define CAT_HPP

#include "AnimatedSprite.hpp"
#include "prank.hpp"

enum catState {
	IDLE,
	TRAVEL,
	PRANK,
	RUN
};

class Cat : public AnimSprite {
public:
	catState state = IDLE;
	void update();
	void setNextPrank(Prank*);
};

#endif // CAT_HPP
