#ifndef PRANK_HPP
#define PRANK_HPP

#include "AnimatedSprite.hpp"
#include "Item.hpp"

class Game;

class Prank{
public:
    Prank(Game* g);
    virtual ~Prank() = default;

    virtual void onFinish();
    virtual void onStart();
    virtual bool isAvailable()=0;
    Anim* catAnim;
    int prankTime = 0; //in milliseconds

    Item* activeItem;
    Game* game;
};


#endif // PRANK_HPP
