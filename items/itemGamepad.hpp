#ifndef ITEM_GAMEPAD_HPP
#define ITEM_GAMEPAD_HPP

#include "../item.hpp"

class Game;

class ItemGamepad: public Item{
public:
    ItemGamepad(Anim *a, Game* g, float layer);
    void onClick() override ;
    void update(sf::Time dt) override ;

    Game* game;
};

#endif // ITEM_GAMEPAD_HPP
