#ifndef PRANK_HPP
#define PRANK_HPP

#include "AnimatedSprite.hpp"
#include "Item.hpp"

class Prank{
public:
    Prank(std::map<std::string, Item*>* its);
    virtual ~Prank() = default;

    virtual void onFinish();
    virtual void onStart();
    virtual bool isAvailable()=0;
    Anim* catAnim;
    int prankTime = 0; //in milliseconds


    std::map<std::string, Item*>* items;

    Item* activeItem;

};


#endif // PRANK_HPP
