#ifndef PRANK_HPP
#define PRANK_HPP

#include "AnimatedSprite.hpp"
#include "Item.hpp"

class Prank{
public:
    Prank(std::map<std::string, Item*>* its);

    virtual bool isAvailable()=0;
    Anim* catAnim;

    std::map<std::string, Item*>* items;
};


#endif // PRANK_HPP
