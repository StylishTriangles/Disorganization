#ifndef PRANK_HPP
#define PRANK_HPP

#include "AnimatedSprite.hpp"
#include "Item.hpp"

class Prank{
public:
    Prank(std::map<std::string, Item*>* its, int xPosition);

    virtual bool isAvailable()=0;
    Anim* catAnim;
    int prankTime = 0; //in milliseconds
    int xCoord;


    std::map<std::string, Item*>* items;

    virtual void onFinish();
};


#endif // PRANK_HPP
